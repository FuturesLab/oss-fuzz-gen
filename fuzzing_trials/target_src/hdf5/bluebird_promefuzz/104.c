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

int LLVMFuzzerTestOneInput_104(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fopen to H5Fget_name
    int ret_H5Aget_num_attrs_eimgx = H5Aget_num_attrs(file_id1);
    if (ret_H5Aget_num_attrs_eimgx < 0){
    	return 0;
    }
    char pasemurr[1024] = "boszi";

    ssize_t ret_H5Fget_name_tucvx = H5Fget_name(file_id1, pasemurr, (size_t )ret_H5Aget_num_attrs_eimgx);

    // End mutation: Producer.APPEND_MUTATOR

    hid_t file_id2 = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function H5Dopen2 with H5Aopen

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of H5Aopen
    hid_t dset_id1 = H5Aopen(file_id1, NULL, H5P_DEFAULT);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dopen2 to H5Awrite_async
    int ret_H5Aget_num_attrs_wvlfd = H5Aget_num_attrs(file_id1);
    if (ret_H5Aget_num_attrs_wvlfd < 0){
    	return 0;
    }
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