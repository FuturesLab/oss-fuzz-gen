// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fget_intent at H5F.c:1540:1 in H5Fpublic.h
// H5Fflush at H5F.c:957:1 in H5Fpublic.h
// H5Fget_access_plist at H5F.c:152:1 in H5Fpublic.h
// H5Fget_vfd_handle at H5F.c:422:1 in H5Fpublic.h
// H5Fget_freespace at H5F.c:1617:1 in H5Fpublic.h
// H5Fset_libver_bounds at H5F.c:2404:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <hdf5.h>

static void test_H5Fget_intent(hid_t file_id) {
    unsigned intent;
    herr_t status = H5Fget_intent(file_id, &intent);
    if (status >= 0) {
        // Successfully retrieved intent
    }
}

static void test_H5Fflush(hid_t file_id) {
    herr_t status = H5Fflush(file_id, H5F_SCOPE_GLOBAL);
    if (status >= 0) {
        // Successfully flushed file
    }
}

static void test_H5Fget_access_plist(hid_t file_id) {
    hid_t plist_id = H5Fget_access_plist(file_id);
    if (plist_id >= 0) {
        // Successfully retrieved access plist
        H5Pclose(plist_id);
    }
}

static void test_H5Fget_vfd_handle(hid_t file_id) {
    void *file_handle;
    herr_t status = H5Fget_vfd_handle(file_id, H5P_DEFAULT, &file_handle);
    if (status >= 0) {
        // Successfully retrieved VFD handle
    }
}

static void test_H5Fget_freespace(hid_t file_id) {
    hssize_t free_space = H5Fget_freespace(file_id);
    if (free_space >= 0) {
        // Successfully retrieved free space
    }
}

static void test_H5Fset_libver_bounds(hid_t file_id) {
    herr_t status = H5Fset_libver_bounds(file_id, H5F_LIBVER_EARLIEST, H5F_LIBVER_LATEST);
    if (status >= 0) {
        // Successfully set libver bounds
    }
}

int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file to work with
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    hid_t file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    test_H5Fget_intent(file_id);
    test_H5Fflush(file_id);
    test_H5Fget_access_plist(file_id);
    test_H5Fget_vfd_handle(file_id);
    test_H5Fget_freespace(file_id);
    test_H5Fset_libver_bounds(file_id);

    H5Fclose(file_id);
    remove("./dummy_file");

    return 0;
}