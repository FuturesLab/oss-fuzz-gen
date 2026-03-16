#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/hdf5/src/H5Dpublic.h"
#include "/src/hdf5/src/H5Fpublic.h"
#include "/src/hdf5/src/H5Ppublic.h"
#include "/src/hdf5/src/H5Spublic.h"

static herr_t dummy_chunk_iter_cb(const hsize_t *offset, unsigned filter_mask, haddr_t addr, hsize_t size, void *op_data) {
    // Dummy callback function for H5Dchunk_iter
    return 0;
}

int LLVMFuzzerTestOneInput_149(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a dummy file for testing
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    hid_t file_id1 = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    hid_t file_id2 = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function H5Dopen2 with H5Aopen
    hid_t dset_id1 = H5Aopen(file_id1, "dataset1", H5P_DEFAULT);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dopen2 to H5Awrite_async

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Aopen to H5Dget_chunk_info
    hid_t ret_H5Dget_access_plist_dxlkt = H5Dget_access_plist(file_id2);
    hsize_t ret_H5Dget_storage_size_quuov = H5Dget_storage_size(0);
    haddr_t ret_H5Dget_offset_qmdgl = H5Dget_offset(dset_id1);
    hsize_t vnmncxnf;
    memset(&vnmncxnf, 0, sizeof(vnmncxnf));
    unsigned int atshqben = 0;

    herr_t ret_H5Dget_chunk_info_kqbrp = H5Dget_chunk_info(ret_H5Dget_access_plist_dxlkt, dset_id1, ret_H5Dget_storage_size_quuov, &vnmncxnf, &atshqben, &ret_H5Dget_offset_qmdgl, NULL);

    // End mutation: Producer.APPEND_MUTATOR

    int ret_H5Aget_num_attrs_wvlfd = H5Aget_num_attrs(file_id1);
    if (ret_H5Aget_num_attrs_wvlfd < 0){
    	return 0;
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Aget_num_attrs to H5Aexists_async

    herr_t ret_H5Aexists_async_iodin = H5Aexists_async((const char *)"w", (const char *)"w", (unsigned int )ret_H5Aget_num_attrs_wvlfd, file_id2, (const char *)"w", NULL, file_id1);

    // End mutation: Producer.APPEND_MUTATOR

    hid_t ret_H5Dget_create_plist_xjxop = H5Dget_create_plist(file_id2);
    hid_t ret_H5Aget_space_hcctc = H5Aget_space(file_id1);
    char xtuuemam[1024] = "cvcgv";

    herr_t ret_H5Awrite_async_zdthh = H5Awrite_async((const char *)"w", NULL, (unsigned int )ret_H5Aget_num_attrs_wvlfd, ret_H5Dget_create_plist_xjxop, dset_id1, xtuuemam, ret_H5Aget_space_hcctc);

    // End mutation: Producer.APPEND_MUTATOR

    hid_t dset_id2 = H5Dopen2(file_id2, "dataset2", H5P_DEFAULT);

    hsize_t nchunks;
    H5Dget_num_chunks(dset_id1, H5S_ALL, &nchunks);
    H5Dget_num_chunks(dset_id2, H5S_ALL, &nchunks);

    hsize_t offset[1] = {0};
    unsigned filter_mask;
    haddr_t addr;
    hsize_t size;

    H5Dget_chunk_info(dset_id1, H5S_ALL, 0, offset, &filter_mask, &addr, &size);
    H5Dget_chunk_info(dset_id2, H5S_ALL, 0, offset, &filter_mask, &addr, &size);

    H5Dget_chunk_info_by_coord(dset_id1, offset, &filter_mask, &addr, &size);
    H5Dget_chunk_info_by_coord(dset_id2, offset, &filter_mask, &addr, &size);

    H5Dchunk_iter(dset_id1, H5P_DEFAULT, dummy_chunk_iter_cb, NULL);
    H5Dchunk_iter(dset_id2, H5P_DEFAULT, dummy_chunk_iter_cb, NULL);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function H5Dclose with H5Fstop_mdc_logging
    H5Fstop_mdc_logging(dset_id1);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    H5Dclose(dset_id2);

    H5Fclose(file_id1);
    H5Fclose(file_id2);

    H5Fdelete("./dummy_file", H5P_DEFAULT);
    H5Fdelete("./dummy_file", H5P_DEFAULT);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function H5Dclose with H5Fstart_mdc_logging
    H5Fstart_mdc_logging(dset_id1);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    H5Dclose(dset_id2);

    H5Fclose(file_id1);
    H5Fclose(file_id2);

    return 0;
}