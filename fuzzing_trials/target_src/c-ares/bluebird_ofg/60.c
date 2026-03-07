#include "ares.h"
#include "stddef.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>  // Include this for the definition of struct hostent
#include <sys/socket.h>  // Include this for AF_INET and AF_INET6

/* Callback function for ares_gethostbyname */
static void host_callback(void *arg, int status, int timeouts, struct hostent *host) {
  /* Handle the callback results here */
  (void)arg;
  (void)status;
  (void)timeouts;
  (void)host;
}

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
  /* Initialize c-ares library */
  ares_library_init(ARES_LIB_INIT_ALL);

  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    return 0;
  }

  /* Ensure the data is null-terminated for use as a string */
  char *name = (char *)malloc(size + 1);
  if (name == NULL) {

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ares_destroy with ares_cancel
    ares_cancel(channel);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    return 0;
  }
  memcpy(name, data, size);
  name[size] = '\0';

  /* Define the family (AF_INET or AF_INET6) */
  int family = AF_INET;  /* or AF_INET6 */

  /* Call the function-under-test */

  // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of ares_gethostbyname
  ares_gethostbyname(channel, name, ARES_NI_TCP, host_callback, NULL);
  // End mutation: Producer.REPLACE_ARG_MUTATOR



  /* Clean up */

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ares_gethostbyname to ares_parse_ns_reply
  struct hostent *enjihvwi;
  memset(&enjihvwi, 0, sizeof(enjihvwi));

  int ret_ares_parse_ns_reply_mhsvg = ares_parse_ns_reply((unsigned char *)name, ARES_OPT_UDP_MAX_QUERIES, &enjihvwi);
  if (ret_ares_parse_ns_reply_mhsvg < 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ares_destroy(channel);
  free(name);
  ares_library_cleanup();

  return 0;
}