#include <sys/stat.h>
#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
  // Ensure size is greater than 0 to have at least one character for the key
  if (size == 0) {
    return 0;
  }

  // Create a UCL object
  ucl_object_t *obj = ucl_object_typed_new(UCL_OBJECT);

  // Use the first part of the data as a key
  char key[256];
  size_t key_len = size < 255 ? size : 255;
  memcpy(key, data, key_len);
  key[key_len] = '\0'; // Ensure null-termination

  // Add a dummy key-value pair to the object
  // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ucl_object_insert_key with ucl_object_replace_key
  ucl_object_replace_key(obj, ucl_object_fromstring("dummy_value"), key, key_len, false);
  // End mutation: Producer.REPLACE_FUNC_MUTATOR

  // Call the function-under-test
  bool result = ucl_object_delete_key(obj, key);

  // Clean up
  ucl_object_unref(obj);

  return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_9(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
