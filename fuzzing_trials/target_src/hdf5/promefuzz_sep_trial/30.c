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
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
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

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fprintf(file, "dummy data");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    write_dummy_file();

    hid_t file_id1 = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id1 < 0) return 0;

    hid_t space_id = H5Screate(H5S_SIMPLE);
    if (space_id < 0) {
        H5Fclose(file_id1);
        return 0;
    }

    hsize_t dims[1] = {10};
    H5Sset_extent_simple(space_id, 1, dims, NULL);

    hid_t dset_id1 = H5Dcreate2(file_id1, "dataset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id1 < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id1);
        return 0;
    }

    H5Dget_offset(dset_id1);

    int data[10] = {0};
    H5Dwrite(dset_id1, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);

    H5Dget_offset(dset_id1);

    H5Dclose(dset_id1);
    H5Fclose(file_id1);

    hid_t file_id2 = H5Fopen("./dummy_file", H5F_ACC_RDONLY, H5P_DEFAULT);
    if (file_id2 < 0) {
        H5Sclose(space_id);
        return 0;
    }

    hid_t dset_id2 = H5Dopen2(file_id2, "dataset", H5P_DEFAULT);
    if (dset_id2 < 0) {
        H5Fclose(file_id2);
        H5Sclose(space_id);
        return 0;
    }

    int read_data[10];
    H5Dread(dset_id2, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, read_data);

    H5Dclose(dset_id2);
    H5Fclose(file_id2);

    file_id1 = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id1 < 0) {
        H5Sclose(space_id);
        return 0;
    }

    dset_id1 = H5Dcreate2(file_id1, "dataset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id1 < 0) {
        H5Fclose(file_id1);
        H5Sclose(space_id);
        return 0;
    }

    H5Dwrite(dset_id1, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);

    H5Dclose(dset_id1);

    dset_id2 = H5Dopen2(file_id1, "dataset", H5P_DEFAULT);
    if (dset_id2 >= 0) {
        H5Dread(dset_id2, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, read_data);
        H5Dclose(dset_id2);
    }

    H5Fclose(file_id1);
    H5Sclose(space_id);

    return 0;
}