#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ares.h>

int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    return 0;
  }

  struct ares_addr_port_node server;
  struct ares_addr_port_node *servers = &server;

  /* Ensure the data is large enough to fill an ares_addr_port_node structure */
  if (size < sizeof(struct ares_addr_port_node)) {
    ares_destroy(channel);
    return 0;
  }

  /* Fill the server structure with data from the fuzzer */
  memcpy(&server, data, sizeof(struct ares_addr_port_node));

  /* Call the function-under-test */
  ares_set_servers_ports(&channel, servers);

  /* Cleanup */
  ares_destroy(channel);

  return 0;
}