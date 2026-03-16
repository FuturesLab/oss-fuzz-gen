#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hdf5.h"

#define DUMMY_FILE "./dummy_file"
#define DATASET_NAME "fuzz_dataset"
#define DATATYPE H5T_NATIVE_INT
#define RANK 2
#define DIM0 4
#define DIM1 6

static void prepare_dummy_file() {
    hid_t file_id, space_id, dset_id;
    hsize_t dims[RANK] = {DIM0, DIM1};
    int data[DIM0][DIM1];
    memset(data, 0, sizeof(data));

    file_id = H5Fcreate(DUMMY_FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    space_id = H5Screate_simple(RANK, dims, NULL);
    dset_id = H5Dcreate2(file_id, DATASET_NAME, DATATYPE, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Dwrite(dset_id, DATATYPE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);

    H5Dclose(dset_id);
    H5Sclose(space_id);
    H5Fclose(file_id);
}

int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size) {
    // Prepare dummy file for testing
    prepare_dummy_file();

    hid_t file_id, space_id, dset_id, mem_space_id;
    hsize_t dims[RANK] = {DIM0, DIM1};
    int buf[DIM0][DIM1];
    herr_t status;

    file_id = H5Fopen(DUMMY_FILE, H5F_ACC_RDWR, H5P_DEFAULT);
    space_id = H5Screate_simple(RANK, dims, NULL);

    // H5Dcreate2
    dset_id = H5Dcreate2(file_id, DATASET_NAME, DATATYPE, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) goto cleanup;

    // H5Dextend
    status = H5Dextend(dset_id, dims);
    if (status < 0) goto cleanup;

    // H5Dget_space
    mem_space_id = H5Dget_space(dset_id);
    if (mem_space_id < 0) goto cleanup;

    // H5Dwrite
    status = H5Dwrite(dset_id, DATATYPE, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);
    if (status < 0) goto cleanup;

    // H5Dget_space
    H5Sclose(mem_space_id);
    mem_space_id = H5Dget_space(dset_id);
    if (mem_space_id < 0) goto cleanup;

    // H5Dread
    status = H5Dread(dset_id, DATATYPE, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);
    if (status < 0) goto cleanup;

cleanup:
    H5Dclose(dset_id);
    H5Sclose(mem_space_id);
    H5Sclose(space_id);
    H5Fclose(file_id);

    return 0;
}