// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Aexists at H5A.c:2364:1 in H5Apublic.h
// H5Aexists_by_name at H5A.c:2474:1 in H5Apublic.h
// H5Aopen at H5A.c:531:1 in H5Apublic.h
// H5Aexists at H5A.c:2364:1 in H5Apublic.h
// H5Aexists_by_name at H5A.c:2474:1 in H5Apublic.h
// H5Aread at H5A.c:1014:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <H5Apublic.h>
#include <H5Fpublic.h>
#include <H5Ppublic.h>

static hid_t create_dummy_file() {
    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return -1;
    }
    return file_id;
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0; // Ensure there's enough data

    hid_t file_id = create_dummy_file();
    if (file_id < 0) return 0;

    const char *attr_name = "test_attribute";
    const char *obj_name = "test_object";
    hid_t attr_id = -1;
    hid_t type_id = H5T_NATIVE_INT;
    int data_buffer[10];

    // H5Aexists
    htri_t exists = H5Aexists(file_id, attr_name);
    if (exists < 0) goto cleanup;

    // H5Aexists_by_name
    exists = H5Aexists_by_name(file_id, obj_name, attr_name, H5P_DEFAULT);
    if (exists < 0) goto cleanup;

    // H5Aopen
    attr_id = H5Aopen(file_id, attr_name, H5P_DEFAULT);
    if (attr_id < 0) goto cleanup;

    // H5Aexists
    exists = H5Aexists(file_id, attr_name);
    if (exists < 0) goto cleanup;

    // H5Aexists_by_name
    exists = H5Aexists_by_name(file_id, obj_name, attr_name, H5P_DEFAULT);
    if (exists < 0) goto cleanup;

    // H5Aread
    herr_t status = H5Aread(attr_id, type_id, data_buffer);
    if (status < 0) goto cleanup;

cleanup:
    // H5Aclose
    if (attr_id >= 0) H5Aclose(attr_id);

    // H5Fclose
    H5Fclose(file_id);

    return 0;
}