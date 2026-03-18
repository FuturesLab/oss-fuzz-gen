#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ares.h>
#include <arpa/inet.h>  // Include for struct in_addr and struct in6_addr
#include <sys/socket.h> // Include for AF_INET and AF_INET6

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    return 0;
  }

  struct ares_addr_node server_node;
  memset(&server_node, 0, sizeof(server_node));

  if (size >= sizeof(struct in_addr)) {
    server_node.family = AF_INET;
    memcpy(&server_node.addr.addr4, data, sizeof(struct in_addr));
  } else if (size >= sizeof(struct in6_addr)) {
    server_node.family = AF_INET6;
    memcpy(&server_node.addr.addr6, data, sizeof(struct in6_addr));
  } else {
    ares_destroy(channel);
    return 0;
  }

  server_node.next = NULL;

  /* Call the function-under-test */
  ares_set_servers(&channel, &server_node);

  ares_destroy(channel);
  return 0;
}