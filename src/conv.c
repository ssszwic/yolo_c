#include "conv.h"

struct conv_param get_conv_param(struct nchw input_shape, uint32_t output_channel, uint8_t kernel, uint8_t stride, 
                                uint8_t padding, bool has_bias, struct tensor weight, struct tensor bias) {
  // caculate output shape
  struct nchw output_shape = {
    .n = input_shape.n,
    .c = output_channel,
    .h = (input_shape.h + 2 * padding - kernel) / stride + 1,
    .w = (input_shape.w + 2 * padding - kernel) / stride + 1,
  };
  output_shape.size = output_shape.n * output_shape.c * output_shape.h * output_shape.w;

  // struct nchw output_shape = {
  //   .n = input_shape.n,
  //   .c = output_channel,
  //   .h = 0,
  //   .w = 0
  // };
  // for (int i = 0; i + kernel - 1 < input_shape.w + 2 * padding; i += stride) {
  //   output_shape.w++;
  // }
  // for (int i = 0; i + kernel - 1 < input_shape.h + 2 * padding; i += stride) {
  //   output_shape.h++;
  // }

  struct conv_param param = {
    .input_shape = input_shape,
    .output_shape = output_shape,
    .kernel = kernel,
    .stride = stride,
    .padding = padding,
    .has_bias = has_bias,
    .weight = weight.data,
    .bias = bias.data
  };

  // check size
  assert(weight.shape.n == param.output_shape.c && weight.shape.c == param.input_shape.c && 
            weight.shape.w <= param.input_shape.w && weight.shape.h <= param.input_shape.h);
  assert(bias.shape.n == 1 && bias.shape.c == 1 && bias.shape.h == 1 && 
            bias.shape.w == param.output_shape.c);
  
  return param;
}

struct tensor pad(struct tensor in, uint8_t padding) {
  // malloc space and set 0
  struct tensor out = create_tensor(create_nchw(in.shape.n, in.shape.c, 
                    in.shape.h + 2 * padding, in.shape.w + 2 * padding), INITIAL_SET_ZERO);
  float *src = in.data;
  float *dst = out.data;
  for(int i = 0; i < in.shape.n * in.shape.c; i++) {
    dst += padding * out.shape.w;
    for(int j = 0; j < in.shape.h; j++) {
      dst += padding;
      // copy whole row
      memcpy(dst, src, sizeof(float) * in.shape.w);
      src += in.shape.w;
      dst += in.shape.w + padding;
    }
    dst += padding * out.shape.w;
  }
  return out;
}

bool compare_nchw(const struct nchw shape1, const struct nchw shape2) {
  if(shape1.n == shape2.n && shape1.c == shape2.c && shape1.h == shape2.h && shape1.w == shape2.w) {
    return true;
  }
  return false;
}

void conv2d(struct tensor output, struct tensor input, struct conv_param *param) {
  assert(compare_nchw(input.shape, param->input_shape) && compare_nchw(output.shape, param->output_shape));
  struct tensor input_pad;
  if(param->padding != 0) {
    input_pad = pad(input, param->padding);
  }
  else {
    input_pad = input;
  }
  save_tensor("/SSD/szw/Work/yolo_c/resource/padding.txt", input_pad);

  // calculate
  float value = 0;
  float *in;
  float *weight;
  float *bias;
  float *out = output.data;
  for (int n = 0; n < output.shape.n; n++) {
    for (int c = 0; c < output.shape.c; c++) {
      // the kernel and bias are same for the one channel of output tensor
      bias = param->bias + c;
      for (int h = 0; h < output.shape.h; h++) {
        for (int w = 0; w < output.shape.w; w++) {
          in = input_pad.data + n * (input_pad.shape.c * input_pad.shape.h * input_pad.shape.w) + 
                          h * param->stride * input_pad.shape.w + w * param->stride;
          weight = param->weight + c * (input_pad.shape.c * param->kernel * param->kernel); // kernel size
          value = 0;
          // kernel
          for (int kc = 0; kc < input_pad.shape.c; kc++) {
            for (int kh = 0; kh < param->kernel; kh++) {
              for (int kw = 0; kw < param->kernel; kw++) {
                value += *(in + kh * input_pad.shape.w + kw) * (*(weight++));
              }
            }
            in += input_pad.shape.h * input_pad.shape.w;
          }
          *(out++) = value + *bias;
        }
      }
    }
  }
  // free padding input
  if(param->padding != 0) {
    free_tensor(input_pad);
  }
}


void print_conv_param(const struct conv_param *param) {
  printf("conv_param:\n");
  printf("  input shape: (%d, %d, %d, %d)\n", param->input_shape.n, 
              param->input_shape.c, param->input_shape.h, param->input_shape.w);
  printf("  output shape: (%d, %d, %d, %d)\n", param->output_shape.n, 
              param->output_shape.c, param->output_shape.h, param->output_shape.w);
  printf("  kernel size: %d\n", param->kernel);
  printf("  stride: %d\n", param->stride);
  printf("  padding: %d\n", param->padding);
  printf("  has bias: %d\n", param->has_bias);
}