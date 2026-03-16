#include <stdint.h>
#include "hdf5.h"
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t file_id = H5I_INVALID_HID; // Invalid file identifier
    hsize_t increment_size = 0;

    // Ensure the data size is sufficient to extract necessary values
    if (size < sizeof(hsize_t)) {
        return 0;
    }

    // Use the data to determine the increment size
    increment_size = *((hsize_t *)data);

    // Open an HDF5 file to get a valid file identifier
    file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Failed to create file, exit
    }

    // Ensure the increment size is a meaningful value
    if (increment_size == 0) {
        increment_size = 1; // Set to a minimum increment size if zero
    }

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fcreate to H5Dcreate2
    hid_t ret_H5Dget_type_wkptc = H5Dget_type(0);
    hid_t ret_H5Aget_type_hjecx = H5Aget_type(0);
    hid_t ret_H5Fget_access_plist_ewire = H5Fget_access_plist(file_id);
    hid_t ret_H5Freopen_lhbbb = H5Freopen(0);
    const char adketbsx[1024] = "fmlhe";

    hid_t ret_H5Dcreate2_ztysl = H5Dcreate2(file_id, adketbsx, ret_H5Dget_type_wkptc, ret_H5Aget_type_hjecx, 0, ret_H5Fget_access_plist_ewire, ret_H5Freopen_lhbbb);

    // End mutation: Producer.APPEND_MUTATOR

    herr_t status = H5Fincrement_filesize(file_id, increment_size);

    // Check the status of the function call
    if (status < 0) {
        // Handle error if needed (e.g., log it, though not necessary for fuzzing)
    }

    // Close the HDF5 file
    H5Fclose(file_id);

    return 0;
}