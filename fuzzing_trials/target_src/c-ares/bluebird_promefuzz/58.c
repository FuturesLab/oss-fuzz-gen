#include <stdint.h>
#include "stddef.h"
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "ares.h"
#include <arpa/nameser.h> // Include this for ns_c_in and ns_t_a

static void dummy_callback(void *arg, int status, int timeouts, unsigned char *abuf, int alen) {
  // Dummy callback function to handle responses
}

static void addrinfo_callback(void *arg, int status, int timeouts, struct ares_addrinfo *res) {
  // Free the addrinfo result to avoid memory leaks
  if (res) {
    ares_freeaddrinfo(res);
  }
}

int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
  ares_channel_t *channel;
  int status;
  char *servers_csv = "8.8.8.8:53,8.8.4.4:53";
  char *name = "example.com";
  char *node = "localhost";
  char *service = "http";
  struct ares_addrinfo_hints hints;
  unsigned char qbuf[512];

  // Initialize c-ares library
  status = ares_library_init(ARES_LIB_INIT_ALL);
  if (status != ARES_SUCCESS) {
    return 0;
  }

  // Initialize the ares channel
  status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    ares_library_cleanup();
    return 0;
  }

  // Set servers using CSV

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ares_init to ares_set_servers_ports_csv
  char ret_ares_dns_rr_get_name_jbinr = ares_dns_rr_get_name(NULL);

  int ret_ares_set_servers_ports_csv_rwqwa = ares_set_servers_ports_csv(channel, &ret_ares_dns_rr_get_name_jbinr);
  if (ret_ares_set_servers_ports_csv_rwqwa < 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ares_set_servers_ports_csv(channel, servers_csv);

  // Fuzz ares_query
  ares_query(channel, name, ns_c_in, ns_t_a, dummy_callback, NULL);

  // Fuzz ares_set_servers_ports_csv
  if (Size > 0) {
    char *data_copy = (char *)malloc(Size + 1);
    if (data_copy) {
      memcpy(data_copy, Data, Size);
      data_copy[Size] = '\0'; // Null-terminate the string to avoid overflow
      ares_set_servers_ports_csv(channel, data_copy);
      free(data_copy);
    }
  }

  // Fuzz ares_getaddrinfo
  memset(&hints, 0, sizeof(hints));
  ares_getaddrinfo(channel, node, service, &hints, addrinfo_callback, NULL);

  // Fuzz ares_search
  ares_search(channel, name, ns_c_in, ns_t_a, dummy_callback, NULL);

  // Fuzz ares_get_servers_csv

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ares_search to ares_set_local_ip6

  ares_set_local_ip6(NULL, (unsigned char *)name);

  // End mutation: Producer.APPEND_MUTATOR

  char *csv = ares_get_servers_csv(channel);
  if (csv) {
    free(csv);
  }

  // Fuzz ares_send
  if (Size > 0 && Size <= sizeof(qbuf)) {
    memcpy(qbuf, Data, Size);

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of ares_send
    ares_send(channel, qbuf, Size, dummy_callback, (void *)"w");
    // End mutation: Producer.REPLACE_ARG_MUTATOR


  }

  // Cleanup
  ares_destroy(channel);
  ares_library_cleanup();

  return 0;
}