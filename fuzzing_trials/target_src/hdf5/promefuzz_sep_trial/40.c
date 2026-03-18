// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fget_metadata_read_retry_info at H5F.c:2104:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
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
#include "H5Ppublic.h"
#include "H5Tpublic.h"
#include "H5Spublic.h"

#define DUMMY_FILE "./dummy_file"
#define DATASET_NAME "dummy_dataset"

static void write_dummy_file() {
    FILE *file = fopen(DUMMY_FILE, "wb");
    if (file) {
        // Write some dummy data to the file
        fwrite("dummy data", 1, 10, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    // Step 1: Prepare environment
    write_dummy_file();

    // Open the file
    hid_t file_id = H5Fopen(DUMMY_FILE, H5F_ACC_RDONLY, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Open the dataset
    hid_t dset_id = H5Dopen2(file_id, DATASET_NAME, H5P_DEFAULT);
    if (dset_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Prepare buffer for reading
    char buf[10];
    herr_t status;

    // Read the dataset
    status = H5Dread(dset_id, H5T_NATIVE_CHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);
    if (status < 0) {
        H5Dclose(dset_id);
        H5Fclose(file_id);
        return 0;
    }

    // Open the dataset again to test multiple opens
    hid_t dset_id2 = H5Dopen2(file_id, DATASET_NAME, H5P_DEFAULT);
    if (dset_id2 < 0) {
        H5Dclose(dset_id);
        H5Fclose(file_id);
        return 0;
    }

    // Read the dataset again
    status = H5Dread(dset_id2, H5T_NATIVE_CHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);
    if (status < 0) {
        H5Dclose(dset_id2);
        H5Dclose(dset_id);
        H5Fclose(file_id);
        return 0;
    }

    // Get metadata read retry info
    H5F_retry_info_t retry_info;
    status = H5Fget_metadata_read_retry_info(file_id, &retry_info);
    if (status < 0) {
        H5Dclose(dset_id2);
        H5Dclose(dset_id);
        H5Fclose(file_id);
        return 0;
    }

    // Free retry info memory if allocated
    for (unsigned i = 0; i < H5F_NUM_METADATA_READ_RETRY_TYPES; i++) {
        if (retry_info.retries[i]) {
            free(retry_info.retries[i]);
        }
    }

    // Close datasets
    H5Dclose(dset_id2);
    H5Dclose(dset_id);

    // Close the file
    H5Fclose(file_id);

    return 0;
}