#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dget_access_plist to H5Fget_mdc_hit_rate

    herr_t ret_H5Fget_mdc_hit_rate_vjzcb = H5Fget_mdc_hit_rate(ret_H5Dget_access_plist_vemmy, NULL);

    // End mutation: Producer.APPEND_MUTATOR

    hid_t ret_H5Aget_space_bmpqr = H5Aget_space(file_id);
    hsize_t ret_H5Aget_storage_size_uzebi = H5Aget_storage_size(file_id);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Aget_storage_size to H5Gget_objtype_by_idx
    hid_t ret_H5Freopen_ejnmg = H5Freopen(0);

    H5G_obj_t ret_H5Gget_objtype_by_idx_txtcm = H5Gget_objtype_by_idx(ret_H5Freopen_ejnmg, ret_H5Aget_storage_size_uzebi);

    // End mutation: Producer.APPEND_MUTATOR

    int ret_H5Aget_num_attrs_jdlwp = H5Aget_num_attrs(file_id);
    if (ret_H5Aget_num_attrs_jdlwp < 0){
    	return 0;
    }
    uint32_t vlqffxdz = 1;

    herr_t ret_H5Dread_chunk2_ejsdy = H5Dread_chunk2(ret_H5Dget_access_plist_vemmy, ret_H5Aget_space_bmpqr, &ret_H5Aget_storage_size_uzebi, &vlqffxdz, (void *)&qahjrtrt, (size_t *)&ret_H5Aget_num_attrs_jdlwp);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dread_chunk2 to H5Aget_info_by_name
    hid_t ret_H5Dget_type_ffgeb = H5Dget_type(ret_H5Aget_space_bmpqr);
    hid_t ret_H5Dget_access_plist_cnnhm = H5Dget_access_plist(ret_H5Aget_space_bmpqr);

    herr_t ret_H5Aget_info_by_name_gvfli = H5Aget_info_by_name(ret_H5Dget_type_ffgeb, &qahjrtrt, &qahjrtrt, NULL, ret_H5Dget_access_plist_cnnhm);

    // End mutation: Producer.APPEND_MUTATOR

        H5Freset_page_buffering_stats(file_id);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }return 0;
}