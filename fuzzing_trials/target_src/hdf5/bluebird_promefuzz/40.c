// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Fget_metadata_read_retry_info at H5F.c:2104:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <hdf5.h>

#define DUMMY_FILE "./dummy_file"
#define DATASET_NAME "dataset"

static hid_t create_dummy_file() {
    hid_t file_id = H5Fcreate(DUMMY_FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        fprintf(stderr, "Failed to create dummy file\n");
        return -1;
    }

    hsize_t dims[1] = {10};
    hid_t space_id = H5Screate_simple(1, dims, NULL);
    if (space_id < 0) {
        fprintf(stderr, "Failed to create dataspace\n");
        H5Fclose(file_id);
        return -1;
    }

    hid_t dset_id = H5Dcreate2(file_id, DATASET_NAME, H5T_NATIVE_INT, space_id, 
                               H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) {
        fprintf(stderr, "Failed to create dataset\n");
        H5Sclose(space_id);
        H5Fclose(file_id);
        return -1;
    }

    int data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    if (H5Dwrite(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data) < 0) {
        fprintf(stderr, "Failed to write data to dataset\n");
    }

    H5Dclose(dset_id);
    H5Sclose(space_id);
    H5Fclose(file_id);

    return 0;
}

int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    if (create_dummy_file() < 0) {
        return 0;
    }

    hid_t file_id = H5Fopen(DUMMY_FILE, H5F_ACC_RDONLY, H5P_DEFAULT);
    if (file_id < 0) {
        fprintf(stderr, "Failed to open file\n");
        return 0;
    }

    hid_t dset_id = H5Dopen2(file_id, DATASET_NAME, H5P_DEFAULT);
    if (dset_id < 0) {
        fprintf(stderr, "Failed to open dataset\n");
        H5Fclose(file_id);
        return 0;
    }

    int buf[10];
    if (H5Dread(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf) < 0) {
        fprintf(stderr, "Failed to read dataset\n");
    }

    H5Dclose(dset_id);

    dset_id = H5Dopen2(file_id, DATASET_NAME, H5P_DEFAULT);
    if (dset_id < 0) {
        fprintf(stderr, "Failed to reopen dataset\n");
        H5Fclose(file_id);
        return 0;
    }

    if (H5Dread(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf) < 0) {
        fprintf(stderr, "Failed to reread dataset\n");
    }

    H5F_retry_info_t retry_info;
    if (H5Fget_metadata_read_retry_info(file_id, &retry_info) < 0) {
        fprintf(stderr, "Failed to get metadata read retry info\n");
    }

    H5Dclose(dset_id);
    H5Fclose(file_id);

    return 0;
}