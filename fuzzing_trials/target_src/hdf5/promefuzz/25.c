// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Aopen at H5A.c:531:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Adelete at H5A.c:2008:1 in H5Apublic.h
// H5Acreate_by_name at H5A.c:366:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Adelete_by_name at H5A.c:2066:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "H5Apublic.h"
#include "H5Fpublic.h"
#include "H5Spublic.h"
#include "H5Tpublic.h"
#include "H5Ppublic.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fprintf(file, "dummy data");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    write_dummy_file();

    hid_t file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    char attr_name[256];
    snprintf(attr_name, sizeof(attr_name), "attr_%zu", Size);

    hid_t attr_id = H5Aopen(file_id, attr_name, H5P_DEFAULT);
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }

    herr_t status = H5Adelete(file_id, attr_name);

    hid_t space_id = H5Screate(H5S_SCALAR);
    hid_t type_id = H5Tcopy(H5T_NATIVE_INT);

    hid_t new_attr_id = H5Acreate_by_name(file_id, ".", attr_name, type_id, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (new_attr_id >= 0) {
        H5Aclose(new_attr_id);
    }

    status = H5Adelete_by_name(file_id, ".", attr_name, H5P_DEFAULT);

    H5Fclose(file_id);

    H5Sclose(space_id);
    H5Tclose(type_id);

    return 0;
}