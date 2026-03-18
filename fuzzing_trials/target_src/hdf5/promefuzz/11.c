// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fclear_elink_file_cache at H5F.c:2194:1 in H5Fpublic.h
// H5Fflush at H5F.c:957:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fis_accessible at H5F.c:464:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fget_access_plist at H5F.c:152:1 in H5Fpublic.h
// H5Freopen at H5F.c:1440:1 in H5Fpublic.h
// H5Fget_access_plist at H5F.c:152:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
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
        fputs("HDF5 dummy data", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t)) {
        return 0;
    }

    write_dummy_file();

    hid_t fapl_id = H5Pcreate(H5P_FILE_ACCESS);
    hid_t file_id, reopened_file_id, access_plist_id;
    htri_t is_accessible;
    herr_t status;

    // H5Fclear_elink_file_cache
    status = H5Fclear_elink_file_cache(fapl_id);

    // H5Fflush
    status = H5Fflush(fapl_id, H5F_SCOPE_LOCAL);

    // H5Fclose
    status = H5Fclose(fapl_id);

    // H5Fis_accessible
    is_accessible = H5Fis_accessible("./dummy_file", H5P_DEFAULT);

    // H5Fopen
    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) {
        H5Pclose(fapl_id);
        return 0;
    }

    // H5Fget_access_plist
    access_plist_id = H5Fget_access_plist(file_id);
    if (access_plist_id >= 0) {
        H5Pclose(access_plist_id);
    }

    // H5Freopen
    reopened_file_id = H5Freopen(file_id);
    if (reopened_file_id >= 0) {
        // H5Fget_access_plist
        access_plist_id = H5Fget_access_plist(reopened_file_id);
        if (access_plist_id >= 0) {
            H5Pclose(access_plist_id);
        }
        H5Fclose(reopened_file_id);
    }

    // H5Fclose
    H5Fclose(file_id);
    H5Pclose(fapl_id);

    return 0;
}