// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Acreate2 at H5A.c:221:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Arename at H5A.c:1646:1 in H5Apublic.h
// H5Arename at H5A.c:1646:1 in H5Apublic.h
// H5Arename at H5A.c:1646:1 in H5Apublic.h
// H5Arename at H5A.c:1646:1 in H5Apublic.h
// H5Arename at H5A.c:1646:1 in H5Apublic.h
// H5Arename_by_name at H5A.c:1756:1 in H5Apublic.h
// H5Arename_by_name at H5A.c:1756:1 in H5Apublic.h
// H5Arename_by_name at H5A.c:1756:1 in H5Apublic.h
// H5Arename_by_name at H5A.c:1756:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "H5Apublic.h"
#include "H5Fpublic.h"
#include "H5Ppublic.h"
#include "H5Tpublic.h"
#include "H5Spublic.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fprintf(file, "Dummy data for HDF5 file.\n");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0; // Ensure there's enough data for meaningful fuzzing

    write_dummy_file();

    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    const char *attr_name = "test_attr";
    hid_t attr_id = H5Acreate2(file_id, attr_name, H5T_NATIVE_INT, H5S_SCALAR, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    char old_name[5];
    char new_name[5];
    char obj_name[5];
    memcpy(old_name, Data, 4); old_name[4] = '\0';
    memcpy(new_name, Data + 4, 4); new_name[4] = '\0';
    memcpy(obj_name, Data + 8, 4); obj_name[4] = '\0';

    H5Arename(file_id, attr_name, old_name);
    H5Arename(file_id, old_name, new_name);
    H5Arename(file_id, new_name, attr_name);
    H5Arename(file_id, attr_name, old_name);
    H5Arename(file_id, old_name, new_name);

    H5Arename_by_name(file_id, obj_name, new_name, old_name, H5P_DEFAULT);
    H5Arename_by_name(file_id, obj_name, old_name, attr_name, H5P_DEFAULT);
    H5Arename_by_name(file_id, obj_name, attr_name, new_name, H5P_DEFAULT);
    H5Arename_by_name(file_id, obj_name, new_name, old_name, H5P_DEFAULT);

    H5Aclose(attr_id);
    H5Fclose(file_id);

    return 0;
}