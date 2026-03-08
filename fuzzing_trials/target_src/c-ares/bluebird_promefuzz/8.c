#include <stdint.h>
#include "stddef.h"
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "ares.h"

static void dummy_callback(void *arg, int status, int timeouts, struct hostent *host) {
    // Dummy callback function for ares_gethostbyaddr
}

int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct ares_options)) return 0;

    // Initialize options
    struct ares_options options;
    memset(&options, 0, sizeof(options));
    options.flags = ARES_FLAG_USEVC;
    options.timeout = 5000;
    options.tries = 3;

    // Initialize channel
    ares_channel_t *channel = NULL;
    int optmask = ARES_OPT_FLAGS | ARES_OPT_TIMEOUTMS | ARES_OPT_TRIES;
    int status = ares_init_options(&channel, &options, optmask);
    if (status != ARES_SUCCESS) {
        return 0;
    }

    // Prepare for ares_getsock
    ares_socket_t socks[ARES_GETSOCK_MAXNUM];
    int numsocks = ares_getsock(channel, socks, ARES_GETSOCK_MAXNUM);

    // Set sortlist
    const char *sortstr = "0.0.0.0/0";
    status = ares_set_sortlist(channel, sortstr);

    // Duplicate channel
    ares_channel_t *dup_channel = NULL;
    status = ares_dup(&dup_channel, channel);
    if (status != ARES_SUCCESS) {
        ares_destroy(channel);
        return 0;
    }

    // Prepare for ares_gethostbyaddr
    if (Size >= sizeof(struct in_addr)) {
        struct in_addr addr;
        memcpy(&addr, Data, sizeof(struct in_addr));
        ares_gethostbyaddr(channel, &addr, sizeof(addr), AF_INET, dummy_callback, NULL);
    }

    // Process file descriptors
    if (numsocks > 0) {
        ares_process_fd(channel, socks[0], ARES_SOCKET_BAD);
    }

    // Cleanup
    ares_destroy(dup_channel);
    ares_destroy(channel);

    return 0;
}