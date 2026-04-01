// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Dcreate_anon at H5D.c:273:1 in H5Dpublic.h
// H5Dset_extent at H5D.c:1991:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <H5Dpublic.h>
#include <H5Fpublic.h>
#include <H5Spublic.h>
#include <H5Tpublic.h>
#include <H5Ppublic.h>

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fprintf(file, "dummy data");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    // Prepare environment
    write_dummy_file();

    hid_t file_id = -1, dataset_id = -1, anon_dataset_id = -1;
    hid_t space_id = -1;
    hsize_t dims[2] = {10, 10};
    herr_t status;

    // Create a new HDF5 file using H5Fcreate
    file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) goto cleanup;

    // Create a dataspace for the dataset
    space_id = H5Screate_simple(2, dims, NULL);
    if (space_id < 0) goto cleanup;

    // Create a dataset in the file using H5Dcreate2
    dataset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) goto cleanup;

    // Create an anonymous dataset using H5Dcreate_anon
    anon_dataset_id = H5Dcreate_anon(file_id, H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT);
    if (anon_dataset_id < 0) goto cleanup;

    // Change the dimensions of the dataset using H5Dset_extent
    dims[0] = (hsize_t)(Size % 20);  // Use input size to influence the dimension
    dims[1] = 10;
    status = H5Dset_extent(dataset_id, dims);
    if (status < 0) goto cleanup;

cleanup:
    if (dataset_id >= 0) H5Dclose(dataset_id);
    if (anon_dataset_id >= 0) H5Dclose(anon_dataset_id);
    if (space_id >= 0) H5Sclose(space_id);
    if (file_id >= 0) H5Fclose(file_id);

    return 0;
}