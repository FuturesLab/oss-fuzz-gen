#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "libyang.h"

int LLVMFuzzerTestOneInput_80(uint8_t const *buf, size_t len) {
  struct ly_ctx *ctx = NULL;
  const char *search_dir = "/tmp";
  uint32_t options = 0;
  LY_ERR err;

  // Initialize the context
  err = ly_ctx_new(search_dir, options, &ctx);
  if (err != LY_SUCCESS || ctx == NULL) {
    fprintf(stderr, "Failed to create context\n");
    return 0;
  }

  // Perform operations on the context if needed
  // ...

  // Destroy the context
  ly_ctx_destroy(ctx);

  return 0;
}