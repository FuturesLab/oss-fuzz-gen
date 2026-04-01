// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aopen at H5A.c:531:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aget_info at H5A.c:1405:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aread at H5A.c:1014:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aget_space at H5A.c:1084:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aget_storage_size at H5A.c:1366:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aopen at H5A.c:531:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Awrite at H5A.c:908:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Apublic.h"
#include "H5Ppublic.h"
#include "H5Tpublic.h"
#include "H5Spublic.h"

#define DUMMY_FILE "./dummy_file"

static void write_dummy_file() {
    FILE *file = fopen(DUMMY_FILE, "w");
    if (file) {
        fputs("HDF5 dummy content", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    write_dummy_file();

    hid_t file_id = H5Fopen(DUMMY_FILE, H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    hid_t dataset_id = H5Dopen2(file_id, "dataset", H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    hid_t attr_id = H5Aopen(dataset_id, "attribute", H5P_DEFAULT);
    if (attr_id < 0) {
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    H5A_info_t ainfo;
    herr_t status = H5Aget_info(attr_id, &ainfo);
    if (status < 0) {
        H5Aclose(attr_id);
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    hid_t type_id = H5T_NATIVE_INT;
    int buffer[10];
    status = H5Aread(attr_id, type_id, buffer);
    if (status < 0) {
        H5Aclose(attr_id);
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    hid_t space_id = H5Aget_space(attr_id);
    if (space_id < 0) {
        H5Aclose(attr_id);
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }
    H5Sclose(space_id);

    hsize_t storage_size = H5Aget_storage_size(attr_id);

    status = H5Aclose(attr_id);
    if (status < 0) {
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    attr_id = H5Aopen(dataset_id, "attribute", H5P_DEFAULT);
    if (attr_id < 0) {
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    status = H5Awrite(attr_id, type_id, buffer);
    if (status < 0) {
        H5Aclose(attr_id);
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    H5Aclose(attr_id);
    H5Dclose(dataset_id);
    H5Fclose(file_id);

    return 0;
}