// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Freset_page_buffering_stats at H5F.c:2485:1 in H5Fpublic.h
// H5Fget_page_buffering_stats at H5F.c:2519:1 in H5Fpublic.h
// H5Freset_page_buffering_stats at H5F.c:2485:1 in H5Fpublic.h
// H5Fget_page_buffering_stats at H5F.c:2519:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "H5Fpublic.h"
#include "H5Ppublic.h" // Include the header for property list constants

static void write_dummy_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file) {
        fputs("dummy data", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's at least some data

    const char *filename = "./dummy_file";
    write_dummy_file(filename);

    hid_t file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    unsigned accesses[2] = {0, 0};
    unsigned hits[2] = {0, 0};
    unsigned misses[2] = {0, 0};
    unsigned evictions[2] = {0, 0};
    unsigned bypasses[2] = {0, 0};

    H5Freset_page_buffering_stats(file_id);
    H5Fget_page_buffering_stats(file_id, accesses, hits, misses, evictions, bypasses);
    H5Freset_page_buffering_stats(file_id);
    H5Fget_page_buffering_stats(file_id, accesses, hits, misses, evictions, bypasses);

    H5Fclose(file_id);
    H5Fclose(file_id); // Attempt to close again to test behavior

    return 0;
}