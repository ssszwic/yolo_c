#ifndef __UTILS_H__
#define __UTILS_H__
#include "commen.h"

#define INITIAL_NOMALLOC        -2 // no malloc space
#define INITIAL_NOSET           -1 // malloc data space and not set
#define INITIAL_SET_ZERO        0  // malloc data space and set 0
#define INITIAL_SET_ONE         1  // malloc data space and set 1
#define INITIAL_SET_RANDFLOAT   2  // malloc data space and set 0 ~ 1 float
#define INITIAL_SET_RANDNUM     3  // malloc data space and set 0 ~ 9 num

struct tensor create_tensor(struct nchw shape, int mode);

struct nchw create_nchw(uint32_t n, uint32_t c, uint32_t h, uint32_t w);

struct tensor load_tensor(char *file_name);

void save_tensor(char *file_name, struct tensor t);

void free_tensor(struct tensor t);

void print_tensor(struct tensor t);

#endif