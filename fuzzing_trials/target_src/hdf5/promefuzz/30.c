// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dget_offset at H5D.c:888:1 in H5Dpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Dget_offset at H5D.c:888:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Spublic.h"
#include "H5Tpublic.h"
#include "H5Ppublic.h"

static void write_dummy_data(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file) {
        const char *data = "dummy data";
        fwrite(data, 1, strlen(data), file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    const char *filename = "./dummy_file";
    write_dummy_data(filename);

    hid_t file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    hid_t space_id = H5Screate(H5S_SCALAR);
    if (space_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    hid_t dset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    H5Dget_offset(dset_id);

    int data = 42;
    H5Dwrite(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, &data);

    H5Dget_offset(dset_id);

    H5Dclose(dset_id);
    H5Fclose(file_id);

    file_id = H5Fopen(filename, H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    dset_id = H5Dopen2(file_id, "dataset", H5P_DEFAULT);
    if (dset_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    int read_data;
    H5Dread(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, &read_data);

    H5Dclose(dset_id);
    H5Fclose(file_id);

    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    dset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    H5Dwrite(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, &data);

    H5Dclose(dset_id);

    dset_id = H5Dopen2(file_id, "dataset", H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    H5Dread(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, &read_data);

    H5Dclose(dset_id);
    H5Fclose(file_id);

    H5Sclose(space_id);

    return 0;
}