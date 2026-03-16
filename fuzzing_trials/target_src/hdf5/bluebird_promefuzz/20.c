// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Drefresh at H5D.c:2096:1 in H5Dpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fstart_swmr_write at H5F.c:2253:1 in H5Fpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Spublic.h"
#include "H5Ppublic.h"

static herr_t handle_error(herr_t status, const char *msg) {
    if (status < 0) {
        fprintf(stderr, "%s\n", msg);
    }
    return status;
}

int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t) * 2) {
        return 0;
    }

    // Initialize identifiers
    hid_t file_id = *((hid_t *)Data);
    hid_t dset_id = *((hid_t *)(Data + sizeof(hid_t)));

    // Dummy buffer
    void *buf = malloc(1024);
    if (!buf) {
        return 0;
    }

    // Refresh dataset
    handle_error(H5Drefresh(dset_id), "Failed to refresh dataset");

    // Read dataset
    handle_error(H5Dread(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf), "Failed to read dataset");

    // Close dataset
    handle_error(H5Dclose(dset_id), "Failed to close dataset");

    // Close file
    handle_error(H5Fclose(file_id), "Failed to close file");

    // Write dataset
    handle_error(H5Dwrite(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf), "Failed to write dataset");

    // Close dataset
    handle_error(H5Dclose(dset_id), "Failed to close dataset");

    // Close file
    handle_error(H5Fclose(file_id), "Failed to close file");

    // Start SWMR write
    handle_error(H5Fstart_swmr_write(file_id), "Failed to start SWMR write");

    // Read dataset
    handle_error(H5Dread(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf), "Failed to read dataset");

    // Close dataset
    handle_error(H5Dclose(dset_id), "Failed to close dataset");

    // Close file
    handle_error(H5Fclose(file_id), "Failed to close file");

    // Close dataset multiple times
    for (int i = 0; i < 4; i++) {
        handle_error(H5Dclose(dset_id), "Failed to close dataset");
    }

    // Close file multiple times
    for (int i = 0; i < 4; i++) {
        handle_error(H5Fclose(file_id), "Failed to close file");
    }

    free(buf);
    return 0;
}