#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient for our needs
    if (size < 5) {
        return 0;
    }

    // Prepare the parameters for H5Fopen
    const char *filename = "testfile.h5"; // Using a fixed filename for testing
    unsigned int flags = (unsigned int)data[0]; // Use the first byte for flags
    hid_t fapl_id = (hid_t)data[1]; // Use the second byte for fapl_id

    // Call the function-under-test
    hid_t file_id = H5Fopen(filename, flags, fapl_id);

    // Close the file if it was successfully opened
    if (file_id >= 0) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function H5Fclose with H5Freset_page_buffering_stats

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fopen to H5Fget_eoa
    haddr_t qahjrtrt;
    memset(&qahjrtrt, 0, sizeof(qahjrtrt));

    herr_t ret_H5Fget_eoa_alzvu = H5Fget_eoa(file_id, &qahjrtrt);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fget_eoa to H5Dread_chunk2

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fget_eoa to H5Dget_chunk_info
    hid_t ret_H5Aget_create_plist_tfsas = H5Aget_create_plist(0);
    hid_t ret_H5Freopen_gbmju = H5Freopen(file_id);
    hsize_t ret_H5Dget_storage_size_nqxjm = H5Dget_storage_size(0);
    unsigned int dnsomdce = 0;

    herr_t ret_H5Dget_chunk_info_vvbil = H5Dget_chunk_info(ret_H5Aget_create_plist_tfsas, ret_H5Freopen_gbmju, 0, &ret_H5Dget_storage_size_nqxjm, &dnsomdce, &qahjrtrt, NULL);

    // End mutation: Producer.APPEND_MUTATOR

    hid_t ret_H5Dget_access_plist_vemmy = H5Dget_access_plist(0);
    hid_t ret_H5Aget_space_bmpqr = H5Aget_space(file_id);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Aget_space to H5Fget_obj_ids
    hid_t ret_H5Aget_create_plist_ityzl = H5Aget_create_plist(ret_H5Dget_access_plist_vemmy);

    ssize_t ret_H5Fget_obj_ids_vokcw = H5Fget_obj_ids(ret_H5Aget_create_plist_ityzl, 0, H5G_NLIBTYPES, &ret_H5Aget_space_bmpqr);

    // End mutation: Producer.APPEND_MUTATOR

    hsize_t ret_H5Aget_storage_size_uzebi = H5Aget_storage_size(file_id);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Aget_storage_size to H5Aiterate2

    herr_t ret_H5Aiterate2_bfaac = H5Aiterate2(file_id, 0, 0, &ret_H5Aget_storage_size_uzebi, NULL, NULL);

    // End mutation: Producer.APPEND_MUTATOR

    int ret_H5Aget_num_attrs_jdlwp = H5Aget_num_attrs(file_id);
    if (ret_H5Aget_num_attrs_jdlwp < 0){
    	return 0;
    }
    uint32_t vlqffxdz = 1;

    herr_t ret_H5Dread_chunk2_ejsdy = H5Dread_chunk2(ret_H5Dget_access_plist_vemmy, ret_H5Aget_space_bmpqr, &ret_H5Aget_storage_size_uzebi, &vlqffxdz, (void *)&qahjrtrt, (size_t *)&ret_H5Aget_num_attrs_jdlwp);

    // End mutation: Producer.APPEND_MUTATOR

        H5Freset_page_buffering_stats(file_id);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }return 0;
}