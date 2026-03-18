#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <ares.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    return 0;
  }

  /* Create a dummy ares_addr_node */
  struct ares_addr_node server;
  server.next = NULL;
  server.family = AF_INET; /* IPv4 */
  if (size >= 4) {
    memcpy(&server.addr.addr4, data, 4); /* Use the first 4 bytes of data for the IP */
  } else {
    server.addr.addr4.s_addr = htonl(INADDR_LOOPBACK); /* Default to 127.0.0.1 if not enough data */
  }

  // Call the function-under-test
  ares_set_servers(&channel, &server);

  // Clean up
  ares_destroy(channel);

  return 0;
}

#ifdef __cplusplus
}
#endif