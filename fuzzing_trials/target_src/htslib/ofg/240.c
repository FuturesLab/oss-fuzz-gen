#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Assuming sam_hdr_t is defined in the relevant library
typedef struct {
    // Dummy structure for demonstration purposes
    int dummy;
} sam_hdr_t;

// Dummy implementation of sam_hdr_add_pg for demonstration
int sam_hdr_add_pg_240(sam_hdr_t *hdr, const char *name, void *extra) {
    // Dummy implementation
    if (hdr == NULL || name == NULL || extra == NULL) {
        return -1; // Indicate error
    }
    printf("sam_hdr_add_pg called with name: %s\n", name);
    return 0; // Indicate success
}

int LLVMFuzzerTestOneInput_240(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Initialize sam_hdr_t
    sam_hdr_t hdr;
    hdr.dummy = 0; // Initialize with a dummy value

    // Create a non-NULL name string
    char name[256];
    size_t name_len = size < 255 ? size : 255;
    memcpy(name, data, name_len);
    name[name_len] = '\0'; // Null-terminate the string

    // Create a non-NULL extra parameter
    int extra_data = 42; // Dummy data
    void *extra = &extra_data;

    // Call the function-under-test
    sam_hdr_add_pg_240(&hdr, name, extra);

    return 0;
}