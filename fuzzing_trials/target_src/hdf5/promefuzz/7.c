// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Acreate2 at H5A.c:221:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Awrite at H5A.c:908:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Adelete_by_idx at H5A.c:2134:1 in H5Apublic.h
// H5Aget_info_by_idx at H5A.c:1501:1 in H5Apublic.h
// H5Aget_name_by_idx at H5A.c:1293:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
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
#include "H5Apublic.h"
#include "H5Fpublic.h"
#include "H5Spublic.h"
#include "H5Tpublic.h"

// Define H5P_DEFAULT if it's not already defined
#ifndef H5P_DEFAULT
#define H5P_DEFAULT 0
#endif

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fprintf(file, "dummy data");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    hid_t file_id, attr_id, space_id, type_id;
    H5A_info_t ainfo;
    herr_t status;
    char attr_name[256];
    write_dummy_file();

    // Open the file
    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Create a dummy dataspace
    space_id = H5Screate(H5S_SCALAR);
    if (space_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Create a dummy datatype
    type_id = H5Tcopy(H5T_NATIVE_INT);
    if (type_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    // Create an attribute
    attr_id = H5Acreate2(file_id, "attr", type_id, space_id, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id < 0) {
        H5Tclose(type_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    // Write to the attribute
    int data = 42;
    status = H5Awrite(attr_id, type_id, &data);
    if (status < 0) {
        H5Aclose(attr_id);
        H5Tclose(type_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    // Close the attribute
    H5Aclose(attr_id);

    // Attempt to delete and get info by index in various ways
    for (int i = 0; i < 3; i++) {
        H5Adelete_by_idx(file_id, ".", H5_INDEX_NAME, H5_ITER_INC, i, H5P_DEFAULT);
        H5Aget_info_by_idx(file_id, ".", H5_INDEX_NAME, H5_ITER_INC, i, &ainfo, H5P_DEFAULT);
        H5Aget_name_by_idx(file_id, ".", H5_INDEX_NAME, H5_ITER_INC, i, attr_name, sizeof(attr_name), H5P_DEFAULT);
    }

    // Close the dataspace and datatype
    H5Sclose(space_id);
    H5Tclose(type_id);

    // Close the file
    H5Fclose(file_id);

    return 0;
}