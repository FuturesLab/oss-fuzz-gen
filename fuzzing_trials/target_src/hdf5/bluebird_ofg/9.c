#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient for our needs
    if (size < 5) {
        return 0;
    }

    // Prepare the parameters for H5Fopen
    const char *filename = "testfile.h5"; // Using a fixed filename for testing
    unsigned int flags = (unsigned int)data[0]; // Use the first byte for flags
    hid_t fapl_id = (hid_t)data[1]; // Use the second byte for fapl_id

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of H5Fopen
    hid_t file_id = H5Fopen((const char *)"w", flags, fapl_id);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Close the file if it was successfully opened
    if (file_id >= 0) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function H5Fclose with H5Freset_page_buffering_stats

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fopen to H5Fget_eoa
    haddr_t qahjrtrt;
    memset(&qahjrtrt, 0, sizeof(qahjrtrt));

    herr_t ret_H5Fget_eoa_alzvu = H5Fget_eoa(file_id, &qahjrtrt);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fget_eoa to H5Dread_chunk2

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fget_eoa to H5Dget_chunk_info_by_coord
    hid_t ret_H5Dget_access_plist_zsuyv = H5Dget_access_plist(file_id);
    hsize_t ret_H5Aget_storage_size_fcqdh = H5Aget_storage_size(file_id);
    const hsize_t hzvmejsw;
    memset(&hzvmejsw, 0, sizeof(hzvmejsw));
    unsigned int uyqqavvc = 0;

    herr_t ret_H5Dget_chunk_info_by_coord_nmqek = H5Dget_chunk_info_by_coord(ret_H5Dget_access_plist_zsuyv, &hzvmejsw, &uyqqavvc, &qahjrtrt, &ret_H5Aget_storage_size_fcqdh);

    // End mutation: Producer.APPEND_MUTATOR

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
    hsize_t ret_H5Dget_storage_size_domkm = H5Dget_storage_size(file_id);
    hid_t ret_H5Dget_access_plist_hcpkv = H5Dget_access_plist(0);
    hid_t ret_H5Dget_access_plist_errcd = H5Dget_access_plist(file_id);

    hid_t ret_H5Aopen_by_idx_jgrhb = H5Aopen_by_idx(file_id, (const char *)data, 0, 0, ret_H5Dget_storage_size_domkm, ret_H5Dget_access_plist_hcpkv, ret_H5Dget_access_plist_errcd);

    // End mutation: Producer.APPEND_MUTATOR

        H5Freset_page_buffering_stats(file_id);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }return 0;
}