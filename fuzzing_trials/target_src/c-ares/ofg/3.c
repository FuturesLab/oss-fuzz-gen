#include <ares.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <netinet/in.h> // For AF_INET
#include <arpa/inet.h> // For struct hostent

// Dummy callback function that does nothing.
static void host_callback(void *arg, int status, int timeouts, struct hostent *hostent) {
    (void)arg; // Suppress unused parameter warning
    (void)status; // Suppress unused parameter warning
    (void)timeouts; // Suppress unused parameter warning
    (void)hostent; // Suppress unused parameter warning
}

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    ares_channel channel; // Fixed type declaration
    int status = ares_library_init(ARES_LIB_INIT_ALL);
    if (status != ARES_SUCCESS) {
        return 0; // Initialization failed.
    }

    status = ares_init(&channel);
    if (status != ARES_SUCCESS) {
        return 0; // Channel initialization failed.
    }

    // Prepare inputs for the function under test
    const char *name = (const char *)data; // Use the input data as the hostname
    int family = AF_INET; // Use IPv4
    void *arg = NULL; // Argument for the callback

    // Ensure the name is null-terminated
    char name_buffer[256];
    if (size < sizeof(name_buffer) - 1) {
        memcpy(name_buffer, data, size);
        name_buffer[size] = '\0'; // Null-terminate
        name = name_buffer;
    } else {
        name_buffer[0] = '\0'; // Fallback to empty string if too large
    }

    // Call the function under test
    ares_gethostbyname(channel, name, family, host_callback, arg);

    // Cleanup
    ares_destroy(channel);
    ares_library_cleanup();

    return 0;
}