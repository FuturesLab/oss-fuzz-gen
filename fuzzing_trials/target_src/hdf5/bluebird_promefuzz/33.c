// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fflush at H5F.c:957:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fget_file_image at H5F.c:1725:1 in H5Fpublic.h
// H5Fget_file_image at H5F.c:1725:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
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
#define DATASET_NAME "dummy_dataset"

static void initialize_dummy_file() {
    FILE *file = fopen(DUMMY_FILE, "w");
    if (file) {
        fprintf(file, "This is a dummy file for HDF5 testing.\n");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's at least some data

    initialize_dummy_file();

    hid_t file_id = H5Fcreate(DUMMY_FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    hsize_t dims[1] = {Size};
    hid_t space_id = H5Screate_simple(1, dims, NULL);
    if (space_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    hid_t dset_id = H5Dcreate2(file_id, DATASET_NAME, H5T_NATIVE_UINT8, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    herr_t status = H5Dwrite(dset_id, H5T_NATIVE_UINT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, Data);
    if (status < 0) {
        H5Dclose(dset_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    status = H5Fflush(file_id, H5F_SCOPE_LOCAL);
    if (status < 0) {
        H5Dclose(dset_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    ssize_t image_size = H5Fget_file_image(file_id, NULL, 0);
    if (image_size > 0) {
        void *image_buf = malloc(image_size);
        if (image_buf) {
            ssize_t actual_size = H5Fget_file_image(file_id, image_buf, image_size);
            if (actual_size != image_size) {
                free(image_buf);
                H5Dclose(dset_id);
                H5Sclose(space_id);
                H5Fclose(file_id);
                return 0;
            }
            free(image_buf);
        }
    }

    H5Dclose(dset_id);
    H5Sclose(space_id);
    H5Fclose(file_id);

    file_id = H5Fopen(DUMMY_FILE, H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    H5Fclose(file_id);

    return 0;
}