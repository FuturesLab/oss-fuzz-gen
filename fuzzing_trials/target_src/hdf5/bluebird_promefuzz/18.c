// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Diterate at H5D.c:1842:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dfill at H5D.c:1758:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Acreate2 at H5A.c:221:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "H5Dpublic.h"
#include "H5Apublic.h"
#include "H5Fpublic.h"
#include "H5Spublic.h"
#include "H5Ppublic.h"
#include "H5Tpublic.h"

static herr_t dummy_operator(void *elem, hid_t type_id, unsigned ndim, const hsize_t *point, void *operator_data) {
    return 0;
}

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
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
    if (file_id < 0) return 0;

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

    H5Dread(dset_id, H5T_NATIVE_UCHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)Data);
    H5Dread(dset_id, H5T_NATIVE_UCHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)Data);
    H5Dread(dset_id, H5T_NATIVE_UCHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)Data);

    H5Dclose(dset_id);
    H5Sclose(space_id);
    H5Fclose(file_id);

    return 0;
}