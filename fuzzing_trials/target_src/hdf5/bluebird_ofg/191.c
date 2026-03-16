#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_191(const uint8_t *data, size_t size) {
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
    hid_t ret_H5Dget_access_plist_vemmy = H5Dget_access_plist(0);
    hid_t ret_H5Aget_space_bmpqr = H5Aget_space(file_id);
    hsize_t ret_H5Aget_storage_size_uzebi = H5Aget_storage_size(file_id);
    int ret_H5Aget_num_attrs_jdlwp = H5Aget_num_attrs(file_id);
    if (ret_H5Aget_num_attrs_jdlwp < 0){
    	return 0;
    }
    uint32_t vlqffxdz = 1;

    herr_t ret_H5Dread_chunk2_ejsdy = H5Dread_chunk2(ret_H5Dget_access_plist_vemmy, ret_H5Aget_space_bmpqr, &ret_H5Aget_storage_size_uzebi, &vlqffxdz, (void *)&qahjrtrt, (size_t *)&ret_H5Aget_num_attrs_jdlwp);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fopen to H5Aopen_by_idx
    hid_t ret_H5Freopen_dulam = H5Freopen(0);
    hsize_t ret_H5Dget_storage_size_bsvkk = H5Dget_storage_size(0);

    hid_t ret_H5Aopen_by_idx_drazl = H5Aopen_by_idx(ret_H5Freopen_dulam, (const char *)data, 0, 0, ret_H5Dget_storage_size_bsvkk, file_id, file_id);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Aopen_by_idx to H5Aopen
    hid_t ret_H5Aget_space_qmlzt = H5Aget_space(0);

    hid_t ret_H5Aopen_tbirb = H5Aopen(ret_H5Aget_space_qmlzt, NULL, ret_H5Aopen_by_idx_drazl);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fopen to H5Acreate2
    hid_t ret_H5Fget_create_plist_ftxph = H5Fget_create_plist(file_id);
    hid_t ret_H5Dget_create_plist_wvqcl = H5Dget_create_plist(file_id);
    hid_t ret_H5Aget_type_hsohe = H5Aget_type(0);
    hid_t ret_H5Aget_space_ucftc = H5Aget_space(0);

    hid_t ret_H5Acreate2_qhukz = H5Acreate2(ret_H5Fget_create_plist_ftxph, NULL, ret_H5Dget_create_plist_wvqcl, ret_H5Aget_type_hsohe, ret_H5Aget_space_ucftc, file_id);

    // End mutation: Producer.APPEND_MUTATOR

        H5Freset_page_buffering_stats(file_id);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }return 0;
}