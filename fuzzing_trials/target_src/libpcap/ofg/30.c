#include <stdint.h>
#include <stddef.h>
#include <string.h>

// Function signature to be fuzzed
int pcap_parsesrcstr(const char *source, int *type, char *host, char *port, char *name, char *interface);

// Fuzzer entry point
int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for the test
    if (size < 10) {
        return 0;
    }

    // Allocate buffers for the parameters
    char source[256];
    int type;
    char host[256];
    char port[256];
    char name[256];
    char interface[256];

    // Initialize the buffers with the data provided
    size_t copy_size = size < 255 ? size : 255;
    memcpy(source, data, copy_size);
    source[copy_size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    pcap_parsesrcstr(source, &type, host, port, name, interface);

    return 0;
}