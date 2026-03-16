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

int LLVMFuzzerTestOneInput_152(const uint8_t *Data, size_t Size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fopen to H5Dcreate2
    hid_t ret_H5Aget_type_loaal = H5Aget_type(file_id2);
    hid_t ret_H5Aget_type_bbial = H5Aget_type(file_id1);
    hid_t ret_H5Dget_access_plist_skwvw = H5Dget_access_plist(file_id2);
    hid_t ret_H5Aget_space_zmdnj = H5Aget_space(0);
    hid_t ret_H5Aget_space_hodxi = H5Aget_space(file_id2);

    hid_t ret_H5Dcreate2_wtrrh = H5Dcreate2(ret_H5Aget_type_loaal, (const char *)"w", ret_H5Aget_type_bbial, ret_H5Dget_access_plist_skwvw, ret_H5Aget_space_zmdnj, ret_H5Aget_space_hodxi, file_id1);

    // End mutation: Producer.APPEND_MUTATOR

    hid_t dset_id1 = H5Dopen2(file_id1, "dataset1", H5P_DEFAULT);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dopen2 to H5Awrite_async

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dopen2 to H5Gget_num_objs
    hsize_t ret_H5Dget_storage_size_rnrlu = H5Dget_storage_size(dset_id1);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dget_storage_size to H5Adelete_by_idx
    hid_t ret_H5Fget_access_plist_pmokz = H5Fget_access_plist(ret_H5Aget_type_loaal);

    herr_t ret_H5Adelete_by_idx_utzfa = H5Adelete_by_idx(ret_H5Aget_space_hodxi, NULL, 0, 0, ret_H5Dget_storage_size_rnrlu, ret_H5Fget_access_plist_pmokz);

    // End mutation: Producer.APPEND_MUTATOR

    herr_t ret_H5Gget_num_objs_icnxg = H5Gget_num_objs(dset_id1, &ret_H5Dget_storage_size_rnrlu);

    // End mutation: Producer.APPEND_MUTATOR

    hid_t ret_H5Freopen_oszhs = H5Freopen(file_id1);

    herr_t ret_H5Awrite_async_ezlvl = H5Awrite_async((const char *)"w", NULL, -1, dset_id1, ret_H5Freopen_oszhs, (const void *)Data, 0);

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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of H5Dget_chunk_info_by_coord
    H5Dget_chunk_info_by_coord(ret_H5Freopen_oszhs, offset, &filter_mask, &addr, &size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



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