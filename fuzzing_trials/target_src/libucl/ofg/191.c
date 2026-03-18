#include <ucl.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

int LLVMFuzzerTestOneInput_191(const uint8_t *data, size_t size) {
  // Ensure the data is large enough to have a meaningful key
  if (size < 2) {
    return 0;
  }

  // Create a new UCL object
  ucl_object_t *obj = ucl_object_typed_new(UCL_OBJECT);

  // Use the first byte of data as a key length
  size_t key_length = data[0] % (size - 1) + 1;

  // Ensure the key length does not exceed the data size
  if (key_length >= size) {
    key_length = size - 1;
  }

  // Extract the key from the data
  char key[key_length + 1];
  memcpy(key, data + 1, key_length);
  key[key_length] = '\0';

  // Add a dummy key-value pair to the object
  ucl_object_insert_key(obj, ucl_object_fromstring("dummy_value"), key, key_length, false);

  // Call the function under test
  bool result = ucl_object_delete_key(obj, key);

  // Clean up
  ucl_object_unref(obj);

  return 0;
}