// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fget_filesize at H5F.c:1659:1 in H5Fpublic.h
// H5Fget_vfd_handle at H5F.c:422:1 in H5Fpublic.h
// H5Fget_intent at H5F.c:1540:1 in H5Fpublic.h
// H5Fget_info2 at H5F.c:2055:1 in H5Fpublic.h
// H5Fget_name at H5F.c:1999:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <hdf5.h>

#define DUMMY_FILE "./dummy_file"

static hid_t create_dummy_file() {
    hid_t file_id = H5Fcreate(DUMMY_FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        fprintf(stderr, "Failed to create dummy HDF5 file.\n");
        exit(EXIT_FAILURE);
    }
    return file_id;
}

int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t)) {
        return 0;
    }

    // Create a dummy file
    hid_t file_id = create_dummy_file();

    // Prepare variables for API function calls
    hsize_t file_size = 0;
    void *file_handle = NULL;
    unsigned intent = 0;
    H5F_info2_t file_info;
    char file_name[1024];
    ssize_t name_len;

    // Call H5Fget_filesize
    if (H5Fget_filesize(file_id, &file_size) < 0) {
        fprintf(stderr, "H5Fget_filesize failed.\n");
    }

    // Call H5Fget_vfd_handle
    if (H5Fget_vfd_handle(file_id, H5P_DEFAULT, &file_handle) < 0) {
        fprintf(stderr, "H5Fget_vfd_handle failed.\n");
    }

    // Call H5Fget_intent
    if (H5Fget_intent(file_id, &intent) < 0) {
        fprintf(stderr, "H5Fget_intent failed.\n");
    }

    // Call H5Fget_info2
    if (H5Fget_info2(file_id, &file_info) < 0) {
        fprintf(stderr, "H5Fget_info2 failed.\n");
    }

    // Call H5Fget_name
    name_len = H5Fget_name(file_id, file_name, sizeof(file_name));
    if (name_len < 0) {
        fprintf(stderr, "H5Fget_name failed.\n");
    }

    // Close the file
    if (H5Fclose(file_id) < 0) {
        fprintf(stderr, "Failed to close the HDF5 file.\n");
    }

    return 0;
}