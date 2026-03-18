// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate_async at H5F.c:673:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dget_space_async at H5D.c:625:1 in H5Dpublic.h
// H5Freopen_async at H5F.c:1477:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <H5Dpublic.h>
#include <H5Fpublic.h>
#include <H5Spublic.h>
#include <H5Tpublic.h>
#include <H5Ppublic.h>
#include <H5ESpublic.h>

static hid_t create_file(const char *filename) {
    return H5Fcreate_async(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT, H5ES_NONE);
}

static hid_t create_dataset(hid_t file_id, const char *dset_name) {
    hsize_t dims[2] = {10, 10};
    hid_t space_id = H5Screate_simple(2, dims, NULL);
    hid_t dset_id = H5Dcreate_async(file_id, dset_name, H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT, H5ES_NONE);
    H5Sclose(space_id);
    return dset_id;
}

static void write_dataset(hid_t dset_id) {
    int data[10][10] = {0};
    H5Dwrite_async(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data, H5ES_NONE);
}

int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) return 0;
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    hid_t file_id = create_file("./dummy_file");
    if (file_id < 0) return 0;

    hid_t dset_id = create_dataset(file_id, "dset");
    if (dset_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    write_dataset(dset_id);

    hid_t space_id = H5Dget_space_async(dset_id, H5ES_NONE);
    if (space_id >= 0) {
        H5Sclose(space_id);
    }

    hid_t reopened_file_id = H5Freopen_async(file_id, H5ES_NONE);
    if (reopened_file_id >= 0) {
        H5Fclose(reopened_file_id);
    }

    H5Dclose(dset_id);
    H5Fclose(file_id);

    return 0;
}