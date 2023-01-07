#include "utils.h"

struct tensor create_tensor(struct nchw shape, int mode) {
  struct tensor t = {
    .shape = shape,
    .data = NULL
  };
  float *data = NULL;

  if(mode == INITIAL_NOMALLOC) return t;

  data = malloc(sizeof(float) * shape.size);
  assert(data);
  t.data = data;

  if(mode == INITIAL_SET_ZERO) {
    memset(data, 0, sizeof(float) * shape.size);
  }
  else if(mode == INITIAL_SET_ONE) {
    for(int i = 0; i < shape.size; i++) {
      *(data++) = 1;
    }
  }
  else if(mode == INITIAL_SET_RANDFLOAT) {
    // random float [0, 1)
    for(int i = 0; i < shape.size; i++) {
      *(data++) = (float) rand() / RAND_MAX;
    }
  }
  else if(mode == INITIAL_SET_RANDNUM) {
    // random num [0, 9)
    for(int i = 0; i < shape.size; i++) {
      *(data++) = rand() % 10;
    }
  }
  return t;
}

struct nchw create_nchw(uint32_t n, uint32_t c, uint32_t h, uint32_t w) {
  struct nchw shape = {
    .n = n,
    .c = c,
    .h = h,
    .w = w,
    .size = n * c * h * w
  };
  return shape;
}

struct tensor load_tensor(char *file_name) {
  FILE *fd = fopen(file_name, "r");
  uint32_t n, c, h, w;
  int num = fscanf(fd, "%u %u %u %u", &n, &c, &h, &w);
  assert(num == 4);

  struct nchw shape = {
    .n = n,
    .c = c,
    .w = w,
    .h = h,
    .size = n * c * w *h
  };

  float *data = malloc(sizeof(float) * shape.size);
  assert(data);

  float *temp = data;
  for (int i = 0; i < shape.size; i++) {
    num = fscanf(fd, "%f", temp++);
    assert(num == 1);
  }
  fclose(fd);

  struct tensor t = {
    .shape = shape,
    .data = data
  };

  return t;
}

void save_tensor(char *file_name, struct tensor t) {
  FILE *fd = fopen(file_name, "w+");
  fprintf(fd, "%u %u %u %u\n\n\n", t.shape.n, t.shape.c, t.shape.h, t.shape.w);
  for (int n = 0; n < t.shape.n; n++) {
    for (int c = 0; c < t.shape.c; c++) {
      for (int h = 0; h < t.shape.h; h++) {
        for (int w = 0; w < t.shape.w; w++) {
          fprintf(fd, "%f  ", *(t.data++));
        }
        fprintf(fd, "\n");
      }
      fprintf(fd, "\n");
    }
    fprintf(fd, "\n");
  }
  fclose(fd);
}


void free_tensor(struct tensor t) {
  free(t.data);
  t.data = NULL;
}

void print_tensor(struct tensor t) {
  for (int n = 0; n < t.shape.n; n++) {
    printf("n: %d\n", n);
    for (int c = 0; c < t.shape.c; c++) {
      printf("  c: %d\n", c);
      for (int h = 0; h < t.shape.h; h++) {
        printf("    ");
        for (int w = 0; w < t.shape.w; w++) {
          printf("%f  ", *(t.data++));
        }
        printf("\n");
      }
    }
  }
}