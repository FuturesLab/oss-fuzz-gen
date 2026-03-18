#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
  // Ensure there is at least one byte to read
  if (size < 1) {
    return 0;
  }

  // Use the first byte of data to determine the boolean value
  bool bool_value = (data[0] % 2 == 0); // even byte value -> true, odd -> false

  // Call the function-under-test
  ucl_object_t *obj = ucl_object_frombool(bool_value);

  // Normally we would do something with 'obj', like checking its properties
  // or freeing it if necessary, but for this fuzzing harness, we just ensure
  // the function is called.

  // Clean up
  ucl_object_unref(obj);

  return 0;
}