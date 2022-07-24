import torch
from TDPS_CNN_54p_do import *
from onnxsim import simplify
import onnx


model = TDPS_CNN_54p()
model.load_state_dict(torch.load('final_net/a0.09368792921304703.pth', map_location='cpu'))
model.eval()



dummy_input = torch.rand([1, 1, 54, 72])
input_names = ['input_image']
output_names = ['predicted_value']

torch.onnx.export(model,
                  dummy_input,
                  "final_a.onnx",
                  verbose=True,
                  input_names=input_names,
                  output_names=output_names)


onnx_model = onnx.load('final_a.onnx')  # load onnx model
model_simp, check = simplify(onnx_model)
assert check, "Simplified ONNX model could not be validated"
onnx.save(model_simp, 'final_a_sim.onnx')
print('finished exporting onnx')
