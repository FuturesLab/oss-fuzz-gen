// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fget_page_buffering_stats at H5F.c:2519:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Freset_page_buffering_stats at H5F.c:2485:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Freset_page_buffering_stats at H5F.c:2485:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <hdf5.h>

static void fuzz_H5Fget_page_buffering_stats(hid_t file_id) {
    unsigned accesses[2] = {0, 0};
    unsigned hits[2] = {0, 0};
    unsigned misses[2] = {0, 0};
    unsigned evictions[2] = {0, 0};
    unsigned bypasses[2] = {0, 0};

    H5Fget_page_buffering_stats(file_id, accesses, hits, misses, evictions, bypasses);
}

int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    hid_t file_id;
    herr_t status;

    // Create a new HDF5 file using the fuzz data as part of the filename
    char filename[256];
    snprintf(filename, sizeof(filename), "./dummy_file_%zu.h5", Size);
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    if (file_id < 0) {
        // If file creation failed, return
        return 0;
    }

    // Reset page buffering stats
    status = H5Freset_page_buffering_stats(file_id);
    if (status < 0) {
        // Handle error if resetting stats failed
        H5Fclose(file_id);
        return 0;
    }

    // Get page buffering stats
    fuzz_H5Fget_page_buffering_stats(file_id);

    // Reset page buffering stats again
    status = H5Freset_page_buffering_stats(file_id);
    if (status < 0) {
        // Handle error if resetting stats failed
        H5Fclose(file_id);
        return 0;
    }

    // Get page buffering stats again
    fuzz_H5Fget_page_buffering_stats(file_id);

    // Close the file
    status = H5Fclose(file_id);
    if (status < 0) {
        // Handle error if closing file failed
        return 0;
    }

    // Attempt to close the file again to test behavior
    status = H5Fclose(file_id);

    return 0;
}