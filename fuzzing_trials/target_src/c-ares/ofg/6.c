#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <ares.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    return 0;
  }

  struct ares_addr_port_node server_node;
  memset(&server_node, 0, sizeof(server_node));

  if (size >= sizeof(struct in_addr)) {
    memcpy(&server_node.addr.addr4, data, sizeof(struct in_addr));
    server_node.family = AF_INET;
    server_node.tcp_port = 80;  /* Example port, can be any valid port number */
    server_node.udp_port = 53;  /* Example port, can be any valid port number */
  }

  ares_set_servers_ports(&channel, &server_node);

  ares_destroy(channel);

  return 0;
}

#ifdef __cplusplus
}
#endif