#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ares.h>
#include <ares_nameser.h> /* Include for C_IN and T_A */

// Callback function for ares_query
static void query_callback(void *arg, int status, int timeouts, const unsigned char *abuf, int alen) {
    (void)arg; // Suppress unused parameter warning
    (void)status; // Suppress unused parameter warning
    (void)timeouts; // Suppress unused parameter warning
    (void)abuf; // Suppress unused parameter warning
    (void)alen; // Suppress unused parameter warning
    // This is a stub callback function for demonstration purposes.
    // In a real-world scenario, you would handle the query response here.
}

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    ares_channel channel;
    int status = ares_library_init(ARES_LIB_INIT_ALL);
    if (status != ARES_SUCCESS) {
        return 0;
    }

    status = ares_init(&channel);
    if (status != ARES_SUCCESS) {
        ares_library_cleanup();
        return 0;
    }

    // Ensure that data is null-terminated for use as a string
    char *name = (char *)malloc(size + 1);
    if (name == NULL) {
        ares_destroy(channel);
        ares_library_cleanup();
        return 0;
    }
    memcpy(name, data, size);
    name[size] = '\0';

    // Use some default values for dnsclass and type
    int dnsclass = C_IN; /* Internet class */
    int type = T_A; /* A record type */

    // Call the function under test
    ares_query(channel, name, dnsclass, type, query_callback, NULL);

    // Clean up
    free(name);
    ares_destroy(channel);
    ares_library_cleanup();

    return 0;
}