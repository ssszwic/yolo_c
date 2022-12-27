#ifndef __LAYER_H__
#define __LAYER_H__

void conv2d(float *input, float *output, float *weight, float *bias, 
  int kernel, int stride, int padding);

#endif