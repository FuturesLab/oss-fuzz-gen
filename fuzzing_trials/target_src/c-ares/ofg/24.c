#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ares.h>

int LLVMFuzzerTestOneInput_24(const unsigned char *data, size_t size) {
  ares_channel channel = NULL;
  struct ares_options options;
  int optmask = ARES_OPT_FLAGS;

  /* Initialize options with some default values */
  options.flags = ARES_FLAG_USEVC;
  options.timeout = 5000;
  options.tries = 3;
  options.ndots = 1;
  options.udp_port = 53;
  options.tcp_port = 53;
  options.socket_send_buffer_size = 4096;
  options.socket_receive_buffer_size = 4096;

  /* Call the function under test */
  ares_init_options(&channel, &options, optmask);

  /* Cleanup */
  if (channel) {
    ares_destroy(channel);
  }

  return 0;
}