// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fget_create_plist at H5F.c:106:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fget_info1 at H5Fdeprec.c:86:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fget_create_plist at H5F.c:106:1 in H5Fpublic.h
// H5Fset_latest_format at H5Fdeprec.c:206:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fget_access_plist at H5F.c:152:1 in H5Fpublic.h
// H5Fget_info1 at H5Fdeprec.c:86:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fget_create_plist at H5F.c:106:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fget_info1 at H5Fdeprec.c:86:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fget_create_plist at H5F.c:106:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fget_create_plist at H5F.c:106:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <H5Fpublic.h>
#include <H5Ppublic.h>

static void handle_hid_t(hid_t id) {
    if (id >= 0) {
        H5Pclose(id);
    }
}

int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file
    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Close the file
    H5Fclose(file_id);

    // Re-create the file
    file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Get file info
    H5F_info1_t file_info;
    if (H5Fget_info1(file_id, &file_info) < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Get file creation property list
    hid_t plist_id = H5Fget_create_plist(file_id);
    handle_hid_t(plist_id);

    // Set latest format
    H5Fset_latest_format(file_id, Data[0] % 2 == 0);

    // Close the file
    H5Fclose(file_id);

    // Re-create the file
    file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Get file access property list
    plist_id = H5Fget_access_plist(file_id);
    handle_hid_t(plist_id);

    // Get file info again
    if (H5Fget_info1(file_id, &file_info) < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Get file creation property list again
    plist_id = H5Fget_create_plist(file_id);
    handle_hid_t(plist_id);

    // Close the file
    H5Fclose(file_id);

    // Open the file
    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Get file info
    if (H5Fget_info1(file_id, &file_info) < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Get file creation property list
    plist_id = H5Fget_create_plist(file_id);
    handle_hid_t(plist_id);

    // Close the file
    H5Fclose(file_id);

    // Re-create the file
    file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Get file creation property list
    plist_id = H5Fget_create_plist(file_id);
    handle_hid_t(plist_id);

    // Close the file
    H5Fclose(file_id);

    // Open the file
    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Get file creation property list
    plist_id = H5Fget_create_plist(file_id);
    handle_hid_t(plist_id);

    // Close the file
    H5Fclose(file_id);

    return 0;
}