#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>  // Include for malloc and free

// Assume the function is declared in an external library
extern int pcap_parsesrcstr(const char *, int *, char *, char *, char *, char *);

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Define and initialize parameters
    const char *source = (const char *)data;
    int type = 0;
    char errbuf[256];
    char host[256];
    char port[256];
    char name[256];

    // Ensure that the source string is null-terminated
    char *null_terminated_source = (char *)malloc(size + 1);
    if (null_terminated_source == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(null_terminated_source, data, size);
    null_terminated_source[size] = '\0';

    // Call the function-under-test
    pcap_parsesrcstr(null_terminated_source, &type, errbuf, host, port, name);

    // Free allocated memory
    free(null_terminated_source);

    return 0;
}