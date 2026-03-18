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
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "H5Apublic.h"
#include "H5Fpublic.h"
#include "H5Ppublic.h"

static hid_t create_dummy_file() {
    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        fprintf(stderr, "Failed to create dummy file\n");
    }
    return file_id;
}

int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return 0;
    }

    hid_t file_id = create_dummy_file();
    if (file_id < 0) {
        return 0;
    }

    const char *obj_name = "dummy_object";
    const char *attr_name = "dummy_attribute";

    // Convert the first byte of data to a valid hid_t
    hid_t obj_id = Data[0];
    hid_t attr_id = -1;

    // Convert the second byte of data to a valid hid_t
    hid_t lapl_id = Data[1];

    // Invoke H5Aexists
    htri_t exists = H5Aexists(obj_id, attr_name);
    if (exists < 0) {
        fprintf(stderr, "H5Aexists error\n");
    }

    // Invoke H5Aexists_by_name
    htri_t exists_by_name = H5Aexists_by_name(obj_id, obj_name, attr_name, lapl_id);
    if (exists_by_name < 0) {
        fprintf(stderr, "H5Aexists_by_name error\n");
    }

    // Invoke H5Aopen
    attr_id = H5Aopen(obj_id, attr_name, H5P_DEFAULT);
    if (attr_id < 0) {
        fprintf(stderr, "H5Aopen error\n");
    }

    // Re-invoke H5Aexists
    exists = H5Aexists(obj_id, attr_name);
    if (exists < 0) {
        fprintf(stderr, "H5Aexists error\n");
    }

    // Re-invoke H5Aexists_by_name
    exists_by_name = H5Aexists_by_name(obj_id, obj_name, attr_name, lapl_id);
    if (exists_by_name < 0) {
        fprintf(stderr, "H5Aexists_by_name error\n");
    }

    // Prepare a buffer for H5Aread
    char buf[256];

    // Invoke H5Aread
    if (attr_id >= 0) {
        herr_t read_status = H5Aread(attr_id, H5T_NATIVE_CHAR, buf);
        if (read_status < 0) {
            fprintf(stderr, "H5Aread error\n");
        }
    }

    // Invoke H5Aclose
    if (attr_id >= 0) {
        herr_t close_status = H5Aclose(attr_id);
        if (close_status < 0) {
            fprintf(stderr, "H5Aclose error\n");
        }
    }

    // Invoke H5Fclose
    herr_t file_close_status = H5Fclose(file_id);
    if (file_close_status < 0) {
        fprintf(stderr, "H5Fclose error\n");
    }

    return 0;
}