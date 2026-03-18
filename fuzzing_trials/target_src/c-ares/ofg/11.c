#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <ares.h>

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
  /* Ensure that the size is sufficient to extract an integer value for 'code' */
  if (size < sizeof(int)) {
    return 0;
  }

  /* Extract an integer value for 'code' from the input data */
  int code;
  memcpy(&code, data, sizeof(int));

  /* Call the function-under-test */
  const char *error_message = ares_strerror(code);

  /* Since ares_strerror returns a string literal, no need to free the memory */
  /* Just use the error_message in some way to ensure it's accessed */
  if (error_message) {
    /* For fuzzing purposes, we can simply check the length of the message */
    size_t length = 0;
    while (error_message[length] != '\0') {
      length++;
    }
  }

  return 0;
}