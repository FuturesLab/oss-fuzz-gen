// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dget_space at H5D.c:597:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dget_type at H5D.c:706:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dvlen_get_buf_size at H5D.c:1889:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Spublic.h"
#include "H5Tpublic.h"
#include "H5Ppublic.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        const char *dummy_data = "HDF5 dummy data";
        fwrite(dummy_data, sizeof(char), strlen(dummy_data), file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    write_dummy_file();

    hid_t file_id = H5Fopen("./dummy_file", H5F_ACC_RDONLY, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    hid_t dataset_id = H5Dopen2(file_id, "dummy_dataset", H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    hid_t space_id = H5Dget_space(dataset_id);
    if (space_id < 0) {
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    hid_t type_id = H5Dget_type(dataset_id);
    if (type_id < 0) {
        H5Sclose(space_id);
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    hsize_t buf_size;
    if (H5Dvlen_get_buf_size(dataset_id, type_id, space_id, &buf_size) < 0) {
        H5Tclose(type_id);
        H5Sclose(space_id);
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    void *buf = malloc(buf_size);
    if (!buf) {
        H5Tclose(type_id);
        H5Sclose(space_id);
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    if (H5Dread(dataset_id, type_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf) < 0) {
        free(buf);
        H5Tclose(type_id);
        H5Sclose(space_id);
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    free(buf);
    H5Tclose(type_id);
    H5Sclose(space_id);
    H5Dclose(dataset_id);
    H5Fclose(file_id);

    return 0;
}