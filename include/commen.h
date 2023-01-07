#ifndef __COMMEN_H__
#define __COMMEN_H__
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct nchw{
  uint32_t n; // batch
  uint32_t c; // channel
  uint32_t h; // height
  uint32_t w; // width
  uint32_t size;
};

struct tensor{
    struct nchw shape;
    float *data;
};

#endif