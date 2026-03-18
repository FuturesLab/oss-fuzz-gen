#include <ares.h>
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_34(const uint8_t* data, size_t size) {
  if (size < sizeof(int) * 2) {
    return 0;
  }

  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    return 0;
  }

  /* Extract random socket file descriptors from data */
  int read_fd = (int)data[0] % 1024;
  int write_fd = (int)data[1] % 1024;

  /* Call the function under test */
  ares_process_fd(channel, read_fd, write_fd);

  ares_destroy(channel);

  return 0;
}