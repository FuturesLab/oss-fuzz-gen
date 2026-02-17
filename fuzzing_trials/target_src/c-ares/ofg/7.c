#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <ares.h>
#include <arpa/inet.h> // For AF_UNSPEC and SOCK_STREAM

// Function prototype for LLVMFuzzerTestOneInput
int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size);

// Callback function for ares_getaddrinfo
void callback_function(int status, int timeouts, struct ares_addrinfo *info, void *arg) {
    // Handle the callback (for fuzzing purposes, we can just free the info)
    if (info) {
        ares_freeaddrinfo(info);
    }
}

int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    // Ensure we have a valid size for the name and service
    if (size < 2) return 0; // Need at least 1 byte for name and 1 byte for service

    // Create a channel
    ares_channel channel;
    if (ares_init(&channel) != ARES_SUCCESS) {
        return 0; // Failed to initialize ares channel
    }

    // Prepare inputs for the function
    const char *name = (const char *)data; // Cast to const char*
    const char *service = (const char *)(data + 1); // Cast to const char*
    
    // Create hints
    struct ares_addrinfo_hints hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // Allow both IPv4 and IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP

    // Call the function under test
    ares_getaddrinfo(channel, name, service, &hints, callback_function, NULL);

    // Clean up
    ares_destroy(channel);
    return 0;
}