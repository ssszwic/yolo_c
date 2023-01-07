#include "layer.h"
#include "commen.h"
#include "utils.h"
#include "conv.h"

int main() {
//   struct nchw input_shape = {
//     .n = 1,
//     .c = 1,
//     .h = 4,
//     .w = 4
//   };

//   struct nchw weight_shape = {
//     .n = 1,
//     .c = 1,
//     .h = 3,
//     .w = 3
//   };

//   float input[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
//   float weight[9] = {1, 0, 3, 4, 2, 0, 3, 0, 1, 2, 0, 3, 4, 2, 0, 3, 0, 1};
//   float bias[0] = {1, 2};

//   print_tensor(input, input_shape);
//   print_tensor(weight, weight_shape);

//   struct conv_param param = get_conv_param(input_shape, 2, 3, 2, 1, true, weight, bias);

//   print_conv_param(&param);

//   float *output = malloc(sizeof(float) * param.output_shape.n * param.output_shape.c *
//                         param.output_shape.h * param.output_shape.w);
//   conv2d(input, output, &param);
//   print_tensor(output, param.output_shape);
//   struct tensor input = load_tensor("/SSD/szw/Work/yolo_c/resource/input.txt");
//   struct tensor weight = load_tensor("/SSD/szw/Work/yolo_c/resource/weight.txt");
//   struct tensor bias = load_tensor("/SSD/szw/Work/yolo_c/resource/bias.txt");
//   struct conv_param param = get_conv_param(input.shape, 10, 3, 2, 1, true, weight, bias);

//   struct tensor input = load_tensor("/SSD/szw/Work/yolo_c/resource/input.txt");
//   struct tensor weight = load_tensor("/SSD/szw/Work/yolo_c/resource/weight.txt");
//   struct tensor bias = load_tensor("/SSD/szw/Work/yolo_c/resource/bias.txt");
  
  struct tensor input = create_tensor(create_nchw(1, 3, 640, 640), INITIAL_SET_RANDFLOAT);
  struct tensor weight = create_tensor(create_nchw(32, 3, 6, 6), INITIAL_SET_RANDFLOAT);
  struct tensor bias = create_tensor(create_nchw(1, 1, 1, 32), INITIAL_SET_RANDFLOAT);
  struct conv_param param = get_conv_param(input.shape, 32, 6, 2, 2, true, weight, bias);
  
  struct tensor output = create_tensor(param.output_shape, INITIAL_NOSET);
  conv2d(output, input, &param);
//   save_tensor("/SSD/szw/Work/yolo_c/resource/input.txt", input);
//   save_tensor("/SSD/szw/Work/yolo_c/resource/weight.txt", weight);
//   save_tensor("/SSD/szw/Work/yolo_c/resource/bias.txt", bias);
  save_tensor("/SSD/szw/Work/yolo_c/resource/out2.txt", output);

}