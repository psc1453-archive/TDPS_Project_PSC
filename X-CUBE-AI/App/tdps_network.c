/**
  ******************************************************************************
  * @file    tdps_network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Sat Jun 19 17:19:23 2021
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "tdps_network.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



/*
#define AI_TOOLS_VERSION_MAJOR 6
#define AI_TOOLS_VERSION_MINOR 0
#define AI_TOOLS_VERSION_MICRO 0
#define AI_TOOLS_VERSION_EXTRA "RC6"

*/

/*
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 4
#define AI_TOOLS_API_VERSION_MICRO 0
*/

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_tdps_network
 
#undef AI_TDPS_NETWORK_MODEL_SIGNATURE
#define AI_TDPS_NETWORK_MODEL_SIGNATURE     "b4a0cdf80f7df895c1418d66e968a7fd"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Sat Jun 19 17:19:23 2021"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_TDPS_NETWORK_N_BATCHES
#define AI_TDPS_NETWORK_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array input_image_output_array;   /* Array #0 */
AI_STATIC ai_array node_48_output_array;   /* Array #1 */
AI_STATIC ai_array node_51_output_array;   /* Array #2 */
AI_STATIC ai_array node_54_output_array;   /* Array #3 */
AI_STATIC ai_array node_45_output_array;   /* Array #4 */
AI_STATIC ai_array node_46_output_array;   /* Array #5 */
AI_STATIC ai_array predicted_value_output_array;   /* Array #6 */
AI_STATIC ai_array fc3bias_array;   /* Array #7 */
AI_STATIC ai_array fc3weight_array;   /* Array #8 */
AI_STATIC ai_array fc0bias_array;   /* Array #9 */
AI_STATIC ai_array fc0weight_array;   /* Array #10 */
AI_STATIC ai_array node_48_weights_array;   /* Array #11 */
AI_STATIC ai_array node_48_bias_array;   /* Array #12 */
AI_STATIC ai_array node_51_weights_array;   /* Array #13 */
AI_STATIC ai_array node_51_bias_array;   /* Array #14 */
AI_STATIC ai_array node_54_weights_array;   /* Array #15 */
AI_STATIC ai_array node_54_bias_array;   /* Array #16 */
AI_STATIC ai_array node_51_scratch0_array;   /* Array #17 */
AI_STATIC ai_array node_54_scratch0_array;   /* Array #18 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor input_image_output;   /* Tensor #0 */
AI_STATIC ai_tensor node_48_output;   /* Tensor #1 */
AI_STATIC ai_tensor node_51_output;   /* Tensor #2 */
AI_STATIC ai_tensor node_54_output;   /* Tensor #3 */
AI_STATIC ai_tensor node_54_output0;   /* Tensor #4 */
AI_STATIC ai_tensor node_45_output;   /* Tensor #5 */
AI_STATIC ai_tensor node_46_output;   /* Tensor #6 */
AI_STATIC ai_tensor predicted_value_output;   /* Tensor #7 */
AI_STATIC ai_tensor fc3bias;   /* Tensor #8 */
AI_STATIC ai_tensor fc3weight;   /* Tensor #9 */
AI_STATIC ai_tensor fc0bias;   /* Tensor #10 */
AI_STATIC ai_tensor fc0weight;   /* Tensor #11 */
AI_STATIC ai_tensor node_48_weights;   /* Tensor #12 */
AI_STATIC ai_tensor node_48_bias;   /* Tensor #13 */
AI_STATIC ai_tensor node_51_weights;   /* Tensor #14 */
AI_STATIC ai_tensor node_51_bias;   /* Tensor #15 */
AI_STATIC ai_tensor node_54_weights;   /* Tensor #16 */
AI_STATIC ai_tensor node_54_bias;   /* Tensor #17 */
AI_STATIC ai_tensor node_51_scratch0;   /* Tensor #18 */
AI_STATIC ai_tensor node_54_scratch0;   /* Tensor #19 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain node_48_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain node_51_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain node_54_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain node_45_chain;   /* Chain #3 */
AI_STATIC_CONST ai_tensor_chain node_46_chain;   /* Chain #4 */
AI_STATIC_CONST ai_tensor_chain predicted_value_chain;   /* Chain #5 */


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_conv2d node_48_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d_nl_pool node_51_layer; /* Layer #1 */
AI_STATIC ai_layer_conv2d_nl_pool node_54_layer; /* Layer #2 */
AI_STATIC ai_layer_gemm node_45_layer; /* Layer #3 */
AI_STATIC ai_layer_nl node_46_layer; /* Layer #4 */
AI_STATIC ai_layer_gemm predicted_value_layer; /* Layer #5 */




/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  input_image_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 3888, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  node_48_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 14560, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  node_51_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3400, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  node_54_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1536, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  node_45_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 200, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  node_46_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 200, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  predicted_value_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 7, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  fc3bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  fc3weight_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1400, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  fc0bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 200, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  fc0weight_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 307200, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  node_48_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  node_48_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  node_51_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 144, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  node_51_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  node_54_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  node_54_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  node_51_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 544, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  node_54_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 512, AI_STATIC)

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  input_image_output, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 72, 54), AI_STRIDE_INIT(4, 4, 4, 4, 288),
  1, &input_image_output_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  node_48_output, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 70, 52), AI_STRIDE_INIT(4, 4, 4, 16, 1120),
  1, &node_48_output_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  node_51_output, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 34, 25), AI_STRIDE_INIT(4, 4, 4, 16, 544),
  1, &node_51_output_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  node_54_output, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 16, 12), AI_STRIDE_INIT(4, 4, 4, 32, 512),
  1, &node_54_output_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  node_54_output0, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 1536, 1, 1), AI_STRIDE_INIT(4, 4, 4, 6144, 6144),
  1, &node_54_output_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  node_45_output, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 200, 1, 1), AI_STRIDE_INIT(4, 4, 4, 800, 800),
  1, &node_45_output_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  node_46_output, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 200, 1, 1), AI_STRIDE_INIT(4, 4, 4, 800, 800),
  1, &node_46_output_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  predicted_value_output, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 1), AI_STRIDE_INIT(4, 4, 4, 28, 28),
  1, &predicted_value_output_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  fc3bias, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 1), AI_STRIDE_INIT(4, 4, 4, 28, 28),
  1, &fc3bias_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  fc3weight, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 200), AI_STRIDE_INIT(4, 4, 4, 28, 28),
  1, &fc3weight_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  fc0bias, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 200, 1, 1), AI_STRIDE_INIT(4, 4, 4, 800, 800),
  1, &fc0bias_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  fc0weight, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 200, 1, 1536), AI_STRIDE_INIT(4, 4, 4, 800, 800),
  1, &fc0weight_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  node_48_weights, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 4), AI_STRIDE_INIT(4, 4, 4, 12, 36),
  1, &node_48_weights_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  node_48_bias, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &node_48_bias_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  node_51_weights, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 4, 3, 3, 4), AI_STRIDE_INIT(4, 4, 16, 48, 144),
  1, &node_51_weights_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  node_51_bias, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &node_51_bias_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  node_54_weights, AI_STATIC,
  16, 0x0,
  AI_SHAPE_INIT(4, 4, 3, 3, 8), AI_STRIDE_INIT(4, 4, 16, 48, 144),
  1, &node_54_weights_array, NULL)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  node_54_bias, AI_STATIC,
  17, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &node_54_bias_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  node_51_scratch0, AI_STATIC,
  18, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 68, 2), AI_STRIDE_INIT(4, 4, 4, 16, 1088),
  1, &node_51_scratch0_array, NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  node_54_scratch0, AI_STATIC,
  19, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 32, 2), AI_STRIDE_INIT(4, 4, 4, 32, 1024),
  1, &node_54_scratch0_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_48_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_image_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_48_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &node_48_weights, &node_48_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_48_layer, 1,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &node_48_chain,
  &AI_NET_OBJ_INSTANCE, &node_51_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_51_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_48_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_51_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &node_51_weights, &node_51_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_51_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  node_51_layer, 4,
  OPTIMIZED_CONV2D_TYPE, 0x0, NULL,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &node_51_chain,
  &AI_NET_OBJ_INSTANCE, &node_54_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_54_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_51_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_54_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &node_54_weights, &node_54_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_54_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  node_54_layer, 7,
  OPTIMIZED_CONV2D_TYPE, 0x0, NULL,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &node_54_chain,
  &AI_NET_OBJ_INSTANCE, &node_45_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 1, 1), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_45_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &node_54_output0, &fc0weight, &fc0bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_45_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_45_layer, 9,
  GEMM_TYPE, 0x0, NULL,
  gemm, forward_gemm,
  &node_45_chain,
  &AI_NET_OBJ_INSTANCE, &node_46_layer, AI_STATIC, 
  .alpha = 1.0, 
  .beta = 1.0, 
  .tA = 1, 
  .tB = 1, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_46_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_45_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_46_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_46_layer, 10,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &node_46_chain,
  &AI_NET_OBJ_INSTANCE, &predicted_value_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  predicted_value_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &node_46_output, &fc3weight, &fc3bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &predicted_value_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  predicted_value_layer, 11,
  GEMM_TYPE, 0x0, NULL,
  gemm, forward_gemm,
  &predicted_value_chain,
  &AI_NET_OBJ_INSTANCE, &predicted_value_layer, AI_STATIC, 
  .alpha = 1.0, 
  .beta = 1.0, 
  .tA = 1, 
  .tB = 1, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 1237164, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 60976, 1,
                     NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_TDPS_NETWORK_IN_NUM, &input_image_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_TDPS_NETWORK_OUT_NUM, &predicted_value_output),
  &node_48_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool tdps_network_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, 4));
  AI_ASSERT(activations)
  AI_UNUSED(net_ctx)

  {
    /* Updating activations (byte) offsets */
    input_image_output_array.data = AI_PTR(NULL);
    input_image_output_array.data_start = AI_PTR(NULL);
    node_48_output_array.data = AI_PTR(activations + 560);
    node_48_output_array.data_start = AI_PTR(activations + 560);
    node_51_output_array.data = AI_PTR(activations + 0);
    node_51_output_array.data_start = AI_PTR(activations + 0);
    node_54_output_array.data = AI_PTR(activations + 15648);
    node_54_output_array.data_start = AI_PTR(activations + 15648);
    node_45_output_array.data = AI_PTR(activations + 0);
    node_45_output_array.data_start = AI_PTR(activations + 0);
    node_46_output_array.data = AI_PTR(activations + 800);
    node_46_output_array.data_start = AI_PTR(activations + 800);
    predicted_value_output_array.data = AI_PTR(NULL);
    predicted_value_output_array.data_start = AI_PTR(NULL);
    node_51_scratch0_array.data = AI_PTR(activations + 58800);
    node_51_scratch0_array.data_start = AI_PTR(activations + 58800);
    node_54_scratch0_array.data = AI_PTR(activations + 13600);
    node_54_scratch0_array.data_start = AI_PTR(activations + 13600);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool tdps_network_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT(weights)
  AI_UNUSED(net_ctx)

  {
    /* Updating weights (byte) offsets */
    
    fc3bias_array.format |= AI_FMT_FLAG_CONST;
    fc3bias_array.data = AI_PTR(weights + 0);
    fc3bias_array.data_start = AI_PTR(weights + 0);
    fc3weight_array.format |= AI_FMT_FLAG_CONST;
    fc3weight_array.data = AI_PTR(weights + 28);
    fc3weight_array.data_start = AI_PTR(weights + 28);
    fc0bias_array.format |= AI_FMT_FLAG_CONST;
    fc0bias_array.data = AI_PTR(weights + 5628);
    fc0bias_array.data_start = AI_PTR(weights + 5628);
    fc0weight_array.format |= AI_FMT_FLAG_CONST;
    fc0weight_array.data = AI_PTR(weights + 6428);
    fc0weight_array.data_start = AI_PTR(weights + 6428);
    node_48_weights_array.format |= AI_FMT_FLAG_CONST;
    node_48_weights_array.data = AI_PTR(weights + 1235228);
    node_48_weights_array.data_start = AI_PTR(weights + 1235228);
    node_48_bias_array.format |= AI_FMT_FLAG_CONST;
    node_48_bias_array.data = AI_PTR(weights + 1235372);
    node_48_bias_array.data_start = AI_PTR(weights + 1235372);
    node_51_weights_array.format |= AI_FMT_FLAG_CONST;
    node_51_weights_array.data = AI_PTR(weights + 1235388);
    node_51_weights_array.data_start = AI_PTR(weights + 1235388);
    node_51_bias_array.format |= AI_FMT_FLAG_CONST;
    node_51_bias_array.data = AI_PTR(weights + 1235964);
    node_51_bias_array.data_start = AI_PTR(weights + 1235964);
    node_54_weights_array.format |= AI_FMT_FLAG_CONST;
    node_54_weights_array.data = AI_PTR(weights + 1235980);
    node_54_weights_array.data_start = AI_PTR(weights + 1235980);
    node_54_bias_array.format |= AI_FMT_FLAG_CONST;
    node_54_bias_array.data = AI_PTR(weights + 1237132);
    node_54_bias_array.data_start = AI_PTR(weights + 1237132);
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_tdps_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_TDPS_NETWORK_MODEL_NAME,
      .model_signature   = AI_TDPS_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 1195216,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_tdps_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_tdps_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_tdps_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_tdps_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= tdps_network_configure_weights(net_ctx, &params->params);
  ok &= tdps_network_configure_activations(net_ctx, &params->activations);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_tdps_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_tdps_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_TDPS_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

