// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fget_intent at H5F.c:1540:1 in H5Fpublic.h
// H5Fflush at H5F.c:957:1 in H5Fpublic.h
// H5Fget_access_plist at H5F.c:152:1 in H5Fpublic.h
// H5Fget_vfd_handle at H5F.c:422:1 in H5Fpublic.h
// H5Fget_freespace at H5F.c:1617:1 in H5Fpublic.h
// H5Fset_libver_bounds at H5F.c:2404:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <hdf5.h>

static hid_t create_test_file() {
    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        fprintf(stderr, "Failed to create test file\n");
    }
    return file_id;
}

static void test_H5Fget_intent(hid_t file_id) {
    unsigned intent;
    herr_t status = H5Fget_intent(file_id, &intent);
    if (status < 0) {
        fprintf(stderr, "H5Fget_intent failed\n");
    }
}

static void test_H5Fflush(hid_t file_id) {
    herr_t status = H5Fflush(file_id, H5F_SCOPE_GLOBAL);
    if (status < 0) {
        fprintf(stderr, "H5Fflush failed\n");
    }
}

static void test_H5Fget_access_plist(hid_t file_id) {
    hid_t plist_id = H5Fget_access_plist(file_id);
    if (plist_id < 0) {
        fprintf(stderr, "H5Fget_access_plist failed\n");
    } else {
        H5Pclose(plist_id);
    }
}

static void test_H5Fget_vfd_handle(hid_t file_id) {
    void *file_handle;
    herr_t status = H5Fget_vfd_handle(file_id, H5P_DEFAULT, &file_handle);
    if (status < 0) {
        fprintf(stderr, "H5Fget_vfd_handle failed\n");
    }
}

static void test_H5Fget_freespace(hid_t file_id) {
    hssize_t free_space = H5Fget_freespace(file_id);
    if (free_space < 0) {
        fprintf(stderr, "H5Fget_freespace failed\n");
    }
}

static void test_H5Fset_libver_bounds(hid_t file_id) {
    herr_t status = H5Fset_libver_bounds(file_id, H5F_LIBVER_EARLIEST, H5F_LIBVER_LATEST);
    if (status < 0) {
        fprintf(stderr, "H5Fset_libver_bounds failed\n");
    }
}

int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size) {
    hid_t file_id = create_test_file();
    if (file_id < 0) {
        return 0;
    }

    test_H5Fget_intent(file_id);
    test_H5Fflush(file_id);
    test_H5Fget_access_plist(file_id);
    test_H5Fget_vfd_handle(file_id);
    test_H5Fget_freespace(file_id);
    test_H5Fset_libver_bounds(file_id);

    H5Fclose(file_id);
    return 0;
}