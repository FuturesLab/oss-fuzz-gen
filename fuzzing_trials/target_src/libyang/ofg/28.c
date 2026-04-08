#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libyang/src/validation.h"
#include "/src/libyang/build/libyang/context.h"
#include "/src/libyang/build/libyang/tree.h"

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
  struct ly_ctx *ctx = NULL;
  struct lyd_node *root = NULL;
  struct lyd_node *result = NULL;
  const struct lys_module *module = NULL;
  LY_ERR err;

  // Initialize libyang context
  err = ly_ctx_new(NULL, 0, &ctx);
  if (err != LY_SUCCESS) {
    fprintf(stderr, "Failed to create context\n");
    return 0;
  }

  // Load a module to validate against
  const char *schema = "module test {namespace urn:test;prefix t;leaf name {type string;}}";
  module = lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);
  if (!module) {
    fprintf(stderr, "Failed to parse module\n");
    ly_ctx_destroy(ctx);
    return 0;
  }

  // Parse the input data into a data tree
  char *data_str = malloc(size + 1);
  if (!data_str) {
    ly_ctx_destroy(ctx);
    return 0;
  }
  memcpy(data_str, data, size);
  data_str[size] = '\0';

  lyd_parse_data_mem(ctx, data_str, LYD_XML, 0, LYD_VALIDATE_PRESENT, &root);
  free(data_str);

  // Call the function-under-test
  err = lyd_validate_module(&root, module, 0, &result);

  // Clean up
  lyd_free_all(root);
  lyd_free_all(result);
  ly_ctx_destroy(ctx);

  return 0;
}