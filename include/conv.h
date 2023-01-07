#ifndef __CONV_H__
#define __CONV_H__
#include "commen.h"
#include "utils.h"

struct conv_param{
  // param
  struct nchw input_shape;
  struct nchw output_shape;
  uint8_t kernel;
  uint8_t stride;
  uint8_t padding;
  bool has_bias;
  // data
  float *weight;
  float *bias;
};

// caculate output_shape
struct conv_param get_conv_param(struct nchw input_shape, uint32_t output_channel, uint8_t kernel, uint8_t stride, 
                                uint8_t padding, bool has_bias, struct tensor weight, struct tensor bias);

struct tensor pad(struct tensor in, uint8_t padding);

void conv2d(struct tensor output, struct tensor input, struct conv_param *param);

void print_conv_param(const struct conv_param *param);

#endif