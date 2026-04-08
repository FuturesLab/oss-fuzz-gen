#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libyang.h"

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
  struct ly_ctx *ctx = NULL;
  LY_ERR err;

  // Initialize the libyang context
  err = ly_ctx_new(NULL, 0, &ctx);
  if (err != LY_SUCCESS) {
    fprintf(stderr, "Failed to create context\n");
    return 0;
  }

  // Ensure the data is null-terminated
  char *schema_data = (char *)malloc(size + 1);
  if (!schema_data) {
    ly_ctx_destroy(ctx);
    return 0;
  }
  memcpy(schema_data, data, size);
  schema_data[size] = '\0';

  // Parse the schema data into the context
  lys_parse_mem(ctx, schema_data, LYS_IN_YANG, NULL);

  // Call the function-under-test
  int compiled_size = ly_ctx_compiled_size(ctx);
  printf("Compiled size: %d\n", compiled_size);

  // Clean up
  free(schema_data);
  ly_ctx_destroy(ctx);

  return 0;
}