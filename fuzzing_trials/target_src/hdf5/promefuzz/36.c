// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fget_obj_count at H5F.c:216:1 in H5Fpublic.h
// H5Fget_obj_ids at H5F.c:333:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fget_obj_count at H5F.c:216:1 in H5Fpublic.h
// H5Fget_obj_ids at H5F.c:333:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Ppublic.h"
#include "H5Spublic.h"
#include "H5Tpublic.h"

#define DUMMY_FILE "./dummy_file"
#define DATASET_NAME "dset"

static void write_dummy_file() {
    FILE *file = fopen(DUMMY_FILE, "w");
    if (file) {
        fputs("This is a dummy file for HDF5 fuzzing.", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    write_dummy_file();

    hid_t file_id, dataset_id, space_id;
    herr_t status;

    // Create a new file using default properties.
    file_id = H5Fcreate(DUMMY_FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Create a simple dataspace with one dimension.
    hsize_t dims[1] = {10};
    space_id = H5Screate_simple(1, dims, NULL);
    if (space_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Create a dataset in the file.
    dataset_id = H5Dcreate2(file_id, DATASET_NAME, H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    // Get object count and IDs.
    ssize_t obj_count = H5Fget_obj_count(file_id, H5F_OBJ_ALL);
    if (obj_count > 0) {
        hid_t *obj_ids = (hid_t *)malloc(obj_count * sizeof(hid_t));
        if (obj_ids) {
            H5Fget_obj_ids(file_id, H5F_OBJ_ALL, obj_count, obj_ids);
            free(obj_ids);
        }
    }

    // Close the dataset and file.
    H5Dclose(dataset_id);
    H5Sclose(space_id);
    H5Fclose(file_id);

    // Reopen the file and dataset.
    file_id = H5Fopen(DUMMY_FILE, H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    dataset_id = H5Dopen2(file_id, DATASET_NAME, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Close the dataset and file again.
    H5Dclose(dataset_id);
    H5Fclose(file_id);

    // Final object count and IDs.
    obj_count = H5Fget_obj_count(H5F_OBJ_ALL, H5F_OBJ_ALL);
    if (obj_count > 0) {
        hid_t *obj_ids = (hid_t *)malloc(obj_count * sizeof(hid_t));
        if (obj_ids) {
            H5Fget_obj_ids(H5F_OBJ_ALL, H5F_OBJ_ALL, obj_count, obj_ids);
            free(obj_ids);
        }
    }

    return 0;
}