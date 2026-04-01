// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fget_dset_no_attrs_hint at H5F.c:2683:1 in H5Fpublic.h
// H5Fset_dset_no_attrs_hint at H5F.c:2722:1 in H5Fpublic.h
// H5Fget_dset_no_attrs_hint at H5F.c:2683:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <H5Fpublic.h>
#include <H5Ppublic.h> // Include this header for H5P_DEFAULT

static hid_t create_file(const char *filename) {
    return H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
}

static hid_t open_file(const char *filename) {
    return H5Fopen(filename, H5F_ACC_RDWR, H5P_DEFAULT);
}

static void test_dset_no_attrs_hint(hid_t file_id) {
    bool minimize;
    H5Fget_dset_no_attrs_hint(file_id, &minimize);
    H5Fset_dset_no_attrs_hint(file_id, !minimize);
    H5Fget_dset_no_attrs_hint(file_id, &minimize);
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's at least 1 byte for testing

    // Prepare a dummy file
    const char *filename = "./dummy_file";

    // Step 1: Create a new HDF5 file
    hid_t file_id = create_file(filename);
    if (file_id < 0) return 0;

    // Step 2: Test dataset no attributes hint
    test_dset_no_attrs_hint(file_id);

    // Step 3: Close the file
    H5Fclose(file_id);

    // Step 4: Re-open the file
    file_id = open_file(filename);
    if (file_id < 0) return 0;

    // Step 5: Test dataset no attributes hint again
    test_dset_no_attrs_hint(file_id);

    // Step 6: Close the file
    H5Fclose(file_id);

    return 0;
}