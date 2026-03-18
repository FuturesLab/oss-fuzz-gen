// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_library_init at ares_library_init.c:108:5 in ares.h
// ares_init at ares_init.c:67:5 in ares.h
// ares_library_cleanup at ares_library_init.c:139:6 in ares.h
// ares_set_servers_ports at ares_update_servers.c:1245:5 in ares.h
// ares_gethostbyname at ares_gethostbyname.c:99:6 in ares.h
// ares_set_servers_ports at ares_update_servers.c:1245:5 in ares.h
// ares_cancel at ares_cancel.c:34:6 in ares.h
// ares_destroy at ares_destroy.c:32:6 in ares.h
// ares_library_cleanup at ares_library_init.c:139:6 in ares.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>

static void dummy_callback(void *arg, int status, int timeouts, struct hostent *host) {
    // Dummy callback function for ares_gethostbyname
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    ares_channel_t *channel;
    int status;
    struct ares_addr_port_node server;
    char hostname[256] = "example.com"; // Default hostname

    // Initialize ares library
    status = ares_library_init(ARES_LIB_INIT_ALL);
    if (status != ARES_SUCCESS) {
        return 0;
    }

    // Create a new channel
    status = ares_init(&channel);
    if (status != ARES_SUCCESS) {
        ares_library_cleanup();
        return 0;
    }

    // Prepare server address and port
    memset(&server, 0, sizeof(server));
    if (Size >= sizeof(struct ares_addr_port_node)) {
        memcpy(&server, Data, sizeof(struct ares_addr_port_node));
    } else {
        server.family = AF_INET;
        server.addr.addr4.s_addr = htonl(INADDR_LOOPBACK);
        server.udp_port = htons(53);
        server.tcp_port = htons(53);
    }

    // Validate family field to prevent invalid access
    if (server.family != AF_INET && server.family != AF_INET6) {
        server.family = AF_INET;
    }

    // Set servers and ports
    status = ares_set_servers_ports(channel, &server);

    // Perform a DNS lookup
    if (Size > 0 && Size < sizeof(hostname)) {
        memcpy(hostname, Data, Size);
        hostname[Size] = '\0'; // Null-terminate the hostname
    }
    ares_gethostbyname(channel, hostname, AF_INET, dummy_callback, NULL);

    // Set servers and ports again
    status = ares_set_servers_ports(channel, &server);

    // Cancel all ongoing requests
    ares_cancel(channel);

    // Cleanup
    ares_destroy(channel);
    ares_library_cleanup();

    return 0;
}