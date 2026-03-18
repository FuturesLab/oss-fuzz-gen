// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fmount at H5F.c:1183:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fget_obj_count at H5F.c:216:1 in H5Fpublic.h
// H5Funmount at H5F.c:1301:1 in H5Fpublic.h
// H5Funmount at H5F.c:1301:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <H5Fpublic.h>
#include <H5Ppublic.h>

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fputs("dummy content", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    write_dummy_file();

    hid_t file_id, child_id, loc_id;
    herr_t status;
    ssize_t obj_count;

    // Fuzz data for file access flags
    unsigned flags = Data[0] % 2 == 0 ? H5F_ACC_TRUNC : H5F_ACC_EXCL;

    // H5Fcreate and H5Fclose sequence
    for (int i = 0; i < 7; ++i) {
        file_id = H5Fcreate("./dummy_file", flags, H5P_DEFAULT, H5P_DEFAULT);
        if (file_id >= 0) {
            H5Fclose(file_id);
        }
    }

    // H5Fopen and H5Fmount sequence
    loc_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (loc_id >= 0) {
        for (int i = 0; i < 5; ++i) {
            child_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
            if (child_id >= 0) {
                status = H5Fmount(loc_id, "/mount_point", child_id, H5P_DEFAULT);
                H5Fclose(child_id);
            }
        }
        H5Fclose(loc_id);
    }

    // H5Fget_obj_count and H5Funmount sequence
    loc_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (loc_id >= 0) {
        obj_count = H5Fget_obj_count(loc_id, H5F_OBJ_ALL);
        if (obj_count >= 0) {
            H5Funmount(loc_id, "/mount_point");
            H5Funmount(loc_id, "/mount_point");
        }
        H5Fclose(loc_id);
    }

    return 0;
}