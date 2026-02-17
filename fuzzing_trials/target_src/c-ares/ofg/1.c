#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ares.h>
#include <ares_version.h>
#include <netinet/in.h> // Include for sockaddr_in and AF_INET
#include <arpa/inet.h> // Include for inet_ntop

// Declare the function prototype without extern "C"
int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size);

// Callback function for ares_getnameinfo
static void callback_function(void *arg, int status, int timeouts, const char *node, const char *service) {
    // This callback can be used to handle the result of ares_getnameinfo
    (void)arg; // Suppress unused parameter warning
    (void)status; // Suppress unused parameter warning
    (void)timeouts; // Suppress unused parameter warning
    (void)node; // Suppress unused parameter warning
    (void)service; // Suppress unused parameter warning
}

// Define the function as static if it's not intended to be used outside this file
int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    if (size < sizeof(struct in_addr)) {
        return 0; // Ensure we have enough data to fill in the address
    }

    ares_channel channel; // Change to ares_channel
    struct sockaddr_in sa; // Use sockaddr_in directly
    ares_socklen_t salen = sizeof(sa);
    int flags_int = 0;
    void *arg = NULL;

    // Initialize the ares channel
    if (ares_init(&channel) != ARES_SUCCESS) {
        return 0; // Initialization failed, return early
    }

    // Prepare sockaddr_in structure
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET; // Use IPv4 for this example
    memcpy(&sa.sin_addr, data, sizeof(struct in_addr)); // Copy data to address

    // Call ares_getnameinfo with the prepared parameters
    ares_getnameinfo(channel, (const struct sockaddr *)&sa, salen, flags_int, callback_function, arg);

    // Clean up the ares channel
    ares_destroy(channel);
    
    return 0;
}