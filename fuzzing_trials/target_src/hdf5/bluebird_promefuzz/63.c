#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/hdf5/src/H5Dpublic.h"
#include "/src/hdf5/src/H5Apublic.h"
#include "/src/hdf5/src/H5Fpublic.h"
#include "/src/hdf5/src/H5Spublic.h"
#include "/src/hdf5/src/H5Ppublic.h"
#include "/src/hdf5/src/H5Tpublic.h"

static herr_t dummy_operator(void *elem, hid_t type_id, unsigned ndim, const hsize_t *point, void *operator_data) {
    return 0;
}

int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t) * 3 + sizeof(hsize_t) * 2) {
        return 0;
    }

    const char *dummy_file = "./dummy_file";
    FILE *file = fopen(dummy_file, "w");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    hid_t file_id = H5Fcreate(dummy_file, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    hsize_t dims[2] = {Size, 1};
    hid_t space_id = H5Screate_simple(2, dims, NULL);
    if (space_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    hid_t dset_id = H5Dcreate2(file_id, "dset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    herr_t status;
    status = H5Dwrite(dset_id, H5T_NATIVE_UCHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, Data);
    if (status < 0) {
        H5Dclose(dset_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    H5Dwrite(dset_id, H5T_NATIVE_UCHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, Data);
    H5Dwrite(dset_id, H5T_NATIVE_UCHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, Data);

    status = H5Diterate((void *)Data, H5T_NATIVE_UCHAR, space_id, dummy_operator, NULL);
    if (status < 0) {
        H5Dclose(dset_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    status = H5Dfill(Data, H5T_NATIVE_UCHAR, (void *)Data, H5T_NATIVE_UCHAR, space_id);
    if (status < 0) {
        H5Dclose(dset_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    hid_t attr_id = H5Acreate2(dset_id, "attr", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Acreate2 to H5Diterate
    hid_t ret_H5Dget_space_vprgn = H5Dget_space(dset_id);

    herr_t ret_H5Diterate_ozlkt = H5Diterate((void *)Data, attr_id, ret_H5Dget_space_vprgn, NULL, (void *)Data);

    // End mutation: Producer.APPEND_MUTATOR

    H5Dread(dset_id, H5T_NATIVE_UCHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)Data);

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of H5Dread
    H5Dread(dset_id, H5T_NATIVE_UCHAR, dset_id, H5S_ALL, H5P_DEFAULT, (void *)Data);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    H5Dread(dset_id, H5T_NATIVE_UCHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)Data);

    H5Dclose(dset_id);
    H5Sclose(space_id);
    H5Fclose(file_id);

    return 0;
}