// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dcreate_anon at H5D.c:273:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dset_extent at H5D.c:1991:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
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

static void write_dummy_data(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file) {
        fputs("Dummy data", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hsize_t)) {
        return 0;
    }

    write_dummy_data("./dummy_file");

    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    hsize_t dims[1] = {Size / sizeof(hsize_t)};
    hid_t space_id = H5Screate_simple(1, dims, NULL);
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

    hid_t anon_dset_id = H5Dcreate_anon(file_id, H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT);
    if (anon_dset_id < 0) {
        H5Dclose(dset_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    herr_t status = H5Dset_extent(dset_id, dims);
    if (status < 0) {
        H5Dclose(anon_dset_id);
        H5Dclose(dset_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    H5Dclose(anon_dset_id);
    H5Dclose(dset_id);
    H5Sclose(space_id);
    H5Fclose(file_id);

    return 0;
}