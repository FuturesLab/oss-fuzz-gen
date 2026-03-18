// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Adelete at H5A.c:2008:1 in H5Apublic.h
// H5Adelete at H5A.c:2008:1 in H5Apublic.h
// H5Aopen_by_idx at H5A.c:792:1 in H5Apublic.h
// H5Aget_name at H5A.c:1228:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Aopen_by_idx at H5A.c:792:1 in H5Apublic.h
// H5Aget_name at H5A.c:1228:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Adelete at H5A.c:2008:1 in H5Apublic.h
// H5Aopen_by_idx at H5A.c:792:1 in H5Apublic.h
// H5Aget_name at H5A.c:1228:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Adelete at H5A.c:2008:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "H5Fpublic.h"
#include "H5Dpublic.h"
#include "H5Apublic.h"
#include "H5Ppublic.h"  // Include for H5P_DEFAULT
#include "H5Tpublic.h"  // Include for H5_ITER_INC

#define DUMMY_FILE "./dummy_file"
#define DUMMY_DATASET "dummy_dataset"

static void write_dummy_file() {
    FILE *file = fopen(DUMMY_FILE, "w");
    if (file) {
        fprintf(file, "Dummy content");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Not enough data to proceed

    write_dummy_file();

    hid_t file_id = H5Fopen(DUMMY_FILE, H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    hid_t dataset_id = H5Dopen2(file_id, DUMMY_DATASET, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Attempt to delete an attribute with the given data as name
    char *attr_name = (char *)malloc(Size + 1);
    if (!attr_name) {
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }
    memcpy(attr_name, Data, Size);
    attr_name[Size] = '\0';

    H5Adelete(dataset_id, attr_name);
    H5Adelete(dataset_id, attr_name);

    // Open attribute by index
    hid_t attr_id = H5Aopen_by_idx(dataset_id, ".", H5_INDEX_NAME, H5_ITER_INC, 0, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id >= 0) {
        char attr_name_buf[256];
        H5Aget_name(attr_id, sizeof(attr_name_buf), attr_name_buf);
        H5Aclose(attr_id);
    }

    attr_id = H5Aopen_by_idx(dataset_id, ".", H5_INDEX_NAME, H5_ITER_INC, 1, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id >= 0) {
        char attr_name_buf[256];
        H5Aget_name(attr_id, sizeof(attr_name_buf), attr_name_buf);
        H5Aclose(attr_id);
    }

    H5Adelete(dataset_id, attr_name);

    attr_id = H5Aopen_by_idx(dataset_id, ".", H5_INDEX_NAME, H5_ITER_INC, 2, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id >= 0) {
        char attr_name_buf[256];
        H5Aget_name(attr_id, sizeof(attr_name_buf), attr_name_buf);
        H5Aclose(attr_id);
    }

    H5Adelete(dataset_id, attr_name);

    free(attr_name);

    H5Dclose(dataset_id);
    H5Fclose(file_id);

    return 0;
}