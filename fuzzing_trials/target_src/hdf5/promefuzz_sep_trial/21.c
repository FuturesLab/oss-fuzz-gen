// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fget_info1 at H5Fdeprec.c:86:1 in H5Fpublic.h
// H5Fget_create_plist at H5F.c:106:1 in H5Fpublic.h
// H5Fset_latest_format at H5Fdeprec.c:206:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fget_access_plist at H5F.c:152:1 in H5Fpublic.h
// H5Fget_info1 at H5Fdeprec.c:86:1 in H5Fpublic.h
// H5Fget_create_plist at H5F.c:106:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fget_info1 at H5Fdeprec.c:86:1 in H5Fpublic.h
// H5Fget_create_plist at H5F.c:106:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fget_create_plist at H5F.c:106:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fget_create_plist at H5F.c:106:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "hdf5.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fputs("HDF5 dummy data", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    write_dummy_file();

    hid_t file_id1, file_id2, file_id3, file_id4;
    H5F_info1_t file_info;
    hid_t plist_id;
    herr_t status;

    // H5Fcreate -> H5Fclose
    file_id1 = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id1 >= 0) {
        H5Fclose(file_id1);
    }

    // H5Fcreate -> H5Fget_info1 -> H5Fget_create_plist -> H5Fset_latest_format -> H5Fclose
    file_id1 = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id1 >= 0) {
        H5Fget_info1(file_id1, &file_info);
        plist_id = H5Fget_create_plist(file_id1);
        if (plist_id >= 0) {
            H5Pclose(plist_id);
        }
        H5Fset_latest_format(file_id1, true);
        H5Fclose(file_id1);
    }

    // H5Fcreate -> H5Fget_access_plist -> H5Fget_info1 -> H5Fget_create_plist -> H5Fclose
    file_id2 = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id2 >= 0) {
        plist_id = H5Fget_access_plist(file_id2);
        if (plist_id >= 0) {
            H5Pclose(plist_id);
        }
        H5Fget_info1(file_id2, &file_info);
        plist_id = H5Fget_create_plist(file_id2);
        if (plist_id >= 0) {
            H5Pclose(plist_id);
        }
        H5Fclose(file_id2);
    }

    // H5Fopen -> H5Fget_info1 -> H5Fget_create_plist -> H5Fclose
    file_id3 = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id3 >= 0) {
        H5Fget_info1(file_id3, &file_info);
        plist_id = H5Fget_create_plist(file_id3);
        if (plist_id >= 0) {
            H5Pclose(plist_id);
        }
        H5Fclose(file_id3);
    }

    // H5Fcreate -> H5Fget_create_plist -> H5Fclose
    file_id4 = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id4 >= 0) {
        plist_id = H5Fget_create_plist(file_id4);
        if (plist_id >= 0) {
            H5Pclose(plist_id);
        }
        H5Fclose(file_id4);
    }

    // H5Fopen -> H5Fget_create_plist -> H5Fclose
    file_id3 = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id3 >= 0) {
        plist_id = H5Fget_create_plist(file_id3);
        if (plist_id >= 0) {
            H5Pclose(plist_id);
        }
        H5Fclose(file_id3);
    }

    return 0;
}