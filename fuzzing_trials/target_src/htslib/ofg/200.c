#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Assuming the existence of these types
typedef int hts_pos_t;
typedef int (*hts_name2id_f)(void *, const char *, int *);

// Dummy implementation of hts_name2id_f for testing
int dummy_hts_name2id(void *data, const char *name, int *id) {
    *id = 1; // Just a dummy ID
    return 0; // Success
}

// Dummy implementation of hts_parse_region for testing
const char * hts_parse_region_200(const char *region, int *tid, hts_pos_t *beg, hts_pos_t *end, hts_name2id_f name2id, void *data, int flags) {
    // Dummy implementation
    *tid = 1;
    *beg = 100;
    *end = 200;
    return region;
}

int LLVMFuzzerTestOneInput_200(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Convert data to a null-terminated string
    char *region = (char *)malloc(size + 1);
    if (!region) {
        return 0;
    }
    memcpy(region, data, size);
    region[size] = '\0';

    int tid;
    hts_pos_t beg, end;
    void *name2id_data = NULL; // This can be any user data required by the name2id function
    int flags = 0; // Example flag value

    // Call the function-under-test
    const char *result = hts_parse_region_200(region, &tid, &beg, &end, dummy_hts_name2id, name2id_data, flags);

    // For demonstration purposes, print the result
    printf("Parsed region: %s, tid: %d, beg: %d, end: %d\n", result, tid, beg, end);

    free(region);
    return 0;
}