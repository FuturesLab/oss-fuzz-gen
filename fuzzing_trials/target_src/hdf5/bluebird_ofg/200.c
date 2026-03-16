#include <stdint.h>
#include "hdf5.h"
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_200(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of H5Fcreate
    file_id = H5Fcreate("fuzz_test.h5", size, H5P_DEFAULT, H5P_DEFAULT);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (file_id < 0) {
        return 0; // Failed to create file, exit
    }

    // Ensure the increment size is a meaningful value
    if (increment_size == 0) {
        increment_size = 1; // Set to a minimum increment size if zero
    }

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fcreate to H5Gmove2


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fcreate to H5Dwrite

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fcreate to H5Fget_obj_count

    ssize_t ret_H5Fget_obj_count_kajov = H5Fget_obj_count(file_id, H5G_NLIBTYPES);

    // End mutation: Producer.APPEND_MUTATOR

    hid_t ret_H5Aget_create_plist_ngwnt = H5Aget_create_plist(file_id);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Aget_create_plist to H5Arename_by_name
    hid_t ret_H5Freopen_hfnul = H5Freopen(file_id);
    const char xrbrdhxv[1024] = "ubgxe";

    herr_t ret_H5Arename_by_name_qdukg = H5Arename_by_name(ret_H5Aget_create_plist_ngwnt, xrbrdhxv, NULL, NULL, ret_H5Freopen_hfnul);

    // End mutation: Producer.APPEND_MUTATOR

    hid_t ret_H5Fget_access_plist_eyolr = H5Fget_access_plist(0);
    hid_t ret_H5Freopen_qpodp = H5Freopen(file_id);
    char ujplmizg[1024] = "mbyne";

    herr_t ret_H5Dwrite_ntvbv = H5Dwrite(file_id, file_id, ret_H5Aget_create_plist_ngwnt, ret_H5Fget_access_plist_eyolr, ret_H5Freopen_qpodp, ujplmizg);

    // End mutation: Producer.APPEND_MUTATOR

    herr_t ret_H5Gmove2_toyyl = H5Gmove2(file_id, (const char *)"w", file_id, (const char *)data);

    // End mutation: Producer.APPEND_MUTATOR

    herr_t status = H5Fincrement_filesize(file_id, increment_size);

    // Check the status of the function call
    if (status < 0) {
        // Handle error if needed (e.g., log it, though not necessary for fuzzing)
    }

    // Close the HDF5 file

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function H5Fclose with H5Dclose
    H5Dclose(file_id);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}