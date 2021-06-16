
#ifdef __cplusplus
 extern "C" {
#endif
/**
  ******************************************************************************
  * @file           : app_x-cube-ai.c
  * @brief          : AI program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V.
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
 /*
  * Description
  *   v1.0 - Minimum template to show how to use the Embedded Client API
  *          model. Only one input and one output is supported. All
  *          memory resources are allocated statically (AI_NETWORK_XX, defines
  *          are used).
  *          Re-target of the printf function is out-of-scope.
  *
  *   For more information, see the embeded documentation:
  *
  *       [1] %X_CUBE_AI_DIR%/Documentation/index.html
  *
  *   X_CUBE_AI_DIR indicates the location where the X-CUBE-AI pack is installed
  *   typical : C:\Users\<user_name>\STM32Cube\Repository\STMicroelectronics\X-CUBE-AI\6.0.0
  */
/* Includes ------------------------------------------------------------------*/
/* System headers */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "app_x-cube-ai.h"
#include "main.h"
#include "ai_datatypes_defines.h"

/* USER CODE BEGIN includes */
#include "ai_math_helpers.h"
/* USER CODE END includes */
/* Global AI objects */
static ai_handle tdps_network = AI_HANDLE_NULL;
static ai_network_report tdps_network_info;

/* Global c-array to handle the activations buffer */
AI_ALIGNED(4)
static ai_u8 activations[AI_TDPS_NETWORK_DATA_ACTIVATIONS_SIZE];

/*  In the case where "--allocate-inputs" option is used, memory buffer can be
 *  used from the activations buffer. This is not mandatory.
 */
#if !defined(AI_TDPS_NETWORK_INPUTS_IN_ACTIVATIONS)
/* Allocate data payload for input tensor */
AI_ALIGNED(32)
static ai_float in_data_s[AI_TDPS_NETWORK_IN_1_SIZE];
#endif

/*  In the case where "--allocate-outputs" option is used, memory buffer can be
 *  used from the activations buffer. This is no mandatory.
 */
#if !defined(AI_TDPS_NETWORK_OUTPUTS_IN_ACTIVATIONS)
/* Allocate data payload for the output tensor */
AI_ALIGNED(32)
static ai_float out_data_s[AI_TDPS_NETWORK_OUT_1_SIZE];
#endif

static void ai_log_err(const ai_error err, const char *fct)
{
  /* USER CODE BEGIN log */
  if (fct)
    printf("TEMPLATE - Error (%s) - type=0x%02x code=0x%02x\r\n", fct,
        err.type, err.code);
  else
    printf("TEMPLATE - Error - type=0x%02x code=0x%02x\r\n", err.type, err.code);

  do {} while (1);
  /* USER CODE END log */
}

static int ai_boostrap(ai_handle w_addr, ai_handle act_addr)
{
  ai_error err;

  /* 1 - Create an instance of the model */
  err = ai_tdps_network_create(&tdps_network, AI_TDPS_NETWORK_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    ai_log_err(err, "ai_tdps_network_create");
    return -1;
  }

  /* 2 - Initialize the instance */
  const ai_network_params params = {
      AI_TDPS_NETWORK_DATA_WEIGHTS(w_addr),
      AI_TDPS_NETWORK_DATA_ACTIVATIONS(act_addr) };

  if (!ai_tdps_network_init(tdps_network, &params)) {
      err = ai_tdps_network_get_error(tdps_network);
      ai_log_err(err, "ai_tdps_network_init");
      return -1;
    }

  /* 3 - Retrieve the network info of the created instance */
  if (!ai_tdps_network_get_info(tdps_network, &tdps_network_info)) {
    err = ai_tdps_network_get_error(tdps_network);
    ai_log_err(err, "ai_tdps_network_get_error");
    ai_tdps_network_destroy(tdps_network);
    tdps_network = AI_HANDLE_NULL;
    return -3;
  }

  return 0;
}

static int ai_run(void *data_in, void *data_out)
{
  ai_i32 batch;

  ai_buffer *ai_input = tdps_network_info.inputs;
  ai_buffer *ai_output = tdps_network_info.outputs;

  ai_input[0].data = AI_HANDLE_PTR(data_in);
  ai_output[0].data = AI_HANDLE_PTR(data_out);

  batch = ai_tdps_network_run(tdps_network, ai_input, ai_output);
  if (batch != 1) {
    ai_log_err(ai_tdps_network_get_error(tdps_network),
        "ai_tdps_network_run");
    return -1;
  }

  return 0;
}

/* USER CODE BEGIN 2 */
extern uint8_t pic_gray[FrameHeight][FrameWidth];
extern float nn_out[7];
extern float path_direction;
ai_float GrayScaleLUT8Bit[256] = {-1.0, -0.9921568627450981, -0.9843137254901961, -0.9764705882352941, -0.9686274509803922, -0.9607843137254902, -0.9529411764705882, -0.9450980392156862, -0.9372549019607843, -0.9294117647058824, -0.9215686274509804, -0.9137254901960784, -0.9058823529411765, -0.8980392156862745, -0.8901960784313725, -0.8823529411764706, -0.8745098039215686, -0.8666666666666667, -0.8588235294117648, -0.8509803921568627, -0.8431372549019608, -0.8352941176470589, -0.8274509803921568, -0.8196078431372549, -0.8117647058823529, -0.803921568627451, -0.7960784313725491, -0.788235294117647, -0.7803921568627451, -0.7725490196078432, -0.7647058823529411, -0.7568627450980392, -0.7490196078431373, -0.7411764705882353, -0.7333333333333334, -0.7254901960784313, -0.7176470588235294, -0.7098039215686274, -0.7019607843137254, -0.6941176470588235, -0.6862745098039216, -0.6784313725490196, -0.6705882352941177, -0.6627450980392157, -0.6549019607843137, -0.6470588235294117, -0.6392156862745098, -0.6313725490196078, -0.6235294117647059, -0.615686274509804, -0.607843137254902, -0.6, -0.592156862745098, -0.584313725490196, -0.5764705882352941, -0.5686274509803921, -0.5607843137254902, -0.5529411764705883, -0.5450980392156863, -0.5372549019607843, -0.5294117647058824, -0.5215686274509803, -0.5137254901960784, -0.5058823529411764, -0.4980392156862745, -0.4901960784313726, -0.48235294117647054, -0.4745098039215686, -0.4666666666666667, -0.45882352941176474, -0.4509803921568627, -0.44313725490196076, -0.43529411764705883, -0.4274509803921569, -0.41960784313725485, -0.4117647058823529, -0.403921568627451, -0.39607843137254906, -0.388235294117647, -0.3803921568627451, -0.37254901960784315, -0.3647058823529412, -0.35686274509803917, -0.34901960784313724, -0.3411764705882353, -0.33333333333333337, -0.3254901960784313, -0.3176470588235294, -0.30980392156862746, -0.3019607843137255, -0.2941176470588235, -0.28627450980392155, -0.2784313725490196, -0.2705882352941177, -0.26274509803921564, -0.2549019607843137, -0.24705882352941178, -0.23921568627450984, -0.2313725490196078, -0.22352941176470587, -0.21568627450980393, -0.207843137254902, -0.19999999999999996, -0.19215686274509802, -0.1843137254901961, -0.17647058823529416, -0.1686274509803921, -0.16078431372549018, -0.15294117647058825, -0.14509803921568631, -0.13725490196078427, -0.12941176470588234, -0.1215686274509804, -0.11372549019607847, -0.10588235294117643, -0.0980392156862745, -0.09019607843137256, -0.08235294117647063, -0.07450980392156858, -0.06666666666666665, -0.05882352941176472, -0.050980392156862786, -0.04313725490196074, -0.03529411764705881, -0.027450980392156876, -0.019607843137254943, -0.0117647058823529, -0.0039215686274509665, 0.0039215686274509665, 0.0117647058823529, 0.019607843137254832, 0.027450980392156765, 0.03529411764705892, 0.04313725490196085, 0.050980392156862786, 0.05882352941176472, 0.06666666666666665, 0.07450980392156858, 0.08235294117647052, 0.09019607843137245, 0.0980392156862746, 0.10588235294117654, 0.11372549019607847, 0.1215686274509804, 0.12941176470588234, 0.13725490196078427, 0.1450980392156862, 0.15294117647058814, 0.1607843137254903, 0.16862745098039222, 0.17647058823529416, 0.1843137254901961, 0.19215686274509802, 0.19999999999999996, 0.2078431372549019, 0.21568627450980382, 0.22352941176470598, 0.2313725490196079, 0.23921568627450984, 0.24705882352941178, 0.2549019607843137, 0.26274509803921564, 0.2705882352941176, 0.2784313725490195, 0.28627450980392166, 0.2941176470588236, 0.3019607843137255, 0.30980392156862746, 0.3176470588235294, 0.3254901960784313, 0.33333333333333326, 0.3411764705882352, 0.34901960784313735, 0.3568627450980393, 0.3647058823529412, 0.37254901960784315, 0.3803921568627451, 0.388235294117647, 0.39607843137254894, 0.4039215686274509, 0.41176470588235303, 0.41960784313725497, 0.4274509803921569, 0.43529411764705883, 0.44313725490196076, 0.4509803921568627, 0.45882352941176463, 0.46666666666666656, 0.4745098039215687, 0.48235294117647065, 0.4901960784313726, 0.4980392156862745, 0.5058823529411764, 0.5137254901960784, 0.5215686274509803, 0.5294117647058822, 0.5372549019607844, 0.5450980392156863, 0.5529411764705883, 0.5607843137254902, 0.5686274509803921, 0.5764705882352941, 0.584313725490196, 0.5921568627450979, 0.6000000000000001, 0.607843137254902, 0.615686274509804, 0.6235294117647059, 0.6313725490196078, 0.6392156862745098, 0.6470588235294117, 0.6549019607843136, 0.6627450980392158, 0.6705882352941177, 0.6784313725490196, 0.6862745098039216, 0.6941176470588235, 0.7019607843137254, 0.7098039215686274, 0.7176470588235293, 0.7254901960784315, 0.7333333333333334, 0.7411764705882353, 0.7490196078431373, 0.7568627450980392, 0.7647058823529411, 0.7725490196078431, 0.780392156862745, 0.7882352941176471, 0.7960784313725491, 0.803921568627451, 0.8117647058823529, 0.8196078431372549, 0.8274509803921568, 0.8352941176470587, 0.8431372549019607, 0.8509803921568628, 0.8588235294117648, 0.8666666666666667, 0.8745098039215686, 0.8823529411764706, 0.8901960784313725, 0.8980392156862744, 0.9058823529411764, 0.9137254901960785, 0.9215686274509804, 0.9294117647058824, 0.9372549019607843, 0.9450980392156862, 0.9529411764705882, 0.9607843137254901, 0.968627450980392, 0.9764705882352942, 0.9843137254901961, 0.9921568627450981, 1.0};

int acquire_and_process_data(ai_float * data)
{
    for(int i = 0; i < 54; i++)
    {
        for(int j = 0; j < 72; j++)
        {
            data[(i-1)*72+(j-1)] = GrayScaleLUT8Bit[pic_gray[i][j]];
        }
    }
  return 0;
}

int post_process(ai_float * data)
{
    ai_float softmax_sum_buffer = 0;
    ai_float exp_buffer[7] = {0};
    ai_float sm_buffer[7] = {0};

    for(int i = 0; i < 7; i++)
    {
        exp_buffer[i] = AI_MATH_EXP(data[i]);
        softmax_sum_buffer += exp_buffer[i];
    }

    for(int i = 0; i < 7; i++)
    {
        sm_buffer[i] = exp_buffer[i] / softmax_sum_buffer;
    }

    float coef[] = {0, 1, 2, 3, 4, 5, 6};
    float result = 0;
    for(int i = 0; i < AI_TDPS_NETWORK_OUT_1_SIZE; i++)
    {
        result += coef[i] * sm_buffer[i];
        nn_out[i] = sm_buffer[i];
    }
    path_direction = result;
  return 0;
}
/* USER CODE END 2 */

/*************************************************************************
  *
  */
void MX_X_CUBE_AI_Init(void)
{
    /* USER CODE BEGIN 5 */
  printf("\r\nTEMPLATE - initialization\r\n");

  ai_boostrap(ai_tdps_network_data_weights_get(), activations);
    /* USER CODE END 5 */
}

void MX_X_CUBE_AI_Process(void)
{
    /* USER CODE BEGIN 6 */
  int res = -1;
  ai_float *in_data = NULL;
  ai_float *out_data = NULL;

  printf("TEMPLATE - run - main loop\r\n");

  if (tdps_network) {

    if ((tdps_network_info.n_inputs != 1) || (tdps_network_info.n_outputs != 1)) {
      ai_error err = {AI_ERROR_INVALID_PARAM, AI_ERROR_CODE_OUT_OF_RANGE};
      ai_log_err(err, "template code should be updated\r\n to support a model with multiple IO");
      return;
    }

    /* 1 - Set the I/O data buffer */

#if AI_NETWORK_INPUTS_IN_ACTIVATIONS
    in_data = network_info.inputs[0].data;
#else
    in_data = in_data_s;
#endif

#if AI_NETWORK_OUTPUTS_IN_ACTIVATIONS
    out_data = network_info.outputs[0].data;
#else
    out_data = out_data_s;
#endif

    if ((!in_data) || (!out_data)) {
      printf("TEMPLATE - I/O buffers are invalid\r\n");
      return;
    }

    /* 2 - main loop */
    do {
      /* 1 - acquire and pre-process input data */
      res = acquire_and_process_data(in_data);
      /* 2 - process the data - call inference engine */
      if (res == 0)
        res = ai_run(in_data, out_data);
      /* 3- post-process the predictions */
      if (res == 0)
        res = post_process(out_data);
      break;
    } while (res==0);
  }

  if (res) {
    ai_error err = {AI_ERROR_INVALID_STATE, AI_ERROR_CODE_NETWORK};
    ai_log_err(err, "Process has FAILED");
  }
    /* USER CODE END 6 */
}
#ifdef __cplusplus
}
#endif
