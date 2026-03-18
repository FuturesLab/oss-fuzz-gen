// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fget_intent at H5F.c:1540:1 in H5Fpublic.h
// H5Fget_freespace at H5F.c:1617:1 in H5Fpublic.h
// H5Fget_vfd_handle at H5F.c:422:1 in H5Fpublic.h
// H5Fset_libver_bounds at H5F.c:2404:1 in H5Fpublic.h
// H5Fget_access_plist at H5F.c:152:1 in H5Fpublic.h
// H5Fflush at H5F.c:957:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <H5Fpublic.h>
#include <H5Ppublic.h>

static hid_t open_dummy_file() {
    // Create a dummy file for testing
    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    return file_id;
}

int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;  // Ensure there's at least some data

    // Open a dummy file
    hid_t file_id = open_dummy_file();
    if (file_id < 0) return 0;

    // Fuzz H5Fget_intent
    unsigned intent;
    herr_t ret_intent = H5Fget_intent(file_id, &intent);

    // Fuzz H5Fget_freespace
    hssize_t freespace = H5Fget_freespace(file_id);

    // Fuzz H5Fget_vfd_handle
    void *file_handle;
    herr_t ret_vfd_handle = H5Fget_vfd_handle(file_id, H5P_DEFAULT, &file_handle);

    // Fuzz H5Fset_libver_bounds
    if (Size >= 2) {
        H5F_libver_t low = (H5F_libver_t)(Data[0] % H5F_LIBVER_NBOUNDS);
        H5F_libver_t high = (H5F_libver_t)(Data[1] % H5F_LIBVER_NBOUNDS);
        herr_t ret_libver_bounds = H5Fset_libver_bounds(file_id, low, high);
    }

    // Fuzz H5Fget_access_plist
    hid_t access_plist = H5Fget_access_plist(file_id);
    if (access_plist >= 0) {
        H5Pclose(access_plist);
    }

    // Fuzz H5Fflush
    H5F_scope_t scope = (H5F_scope_t)(Data[0] % 2);
    herr_t ret_flush = H5Fflush(file_id, scope);

    // Close the file
    H5Fclose(file_id);

    return 0;
}