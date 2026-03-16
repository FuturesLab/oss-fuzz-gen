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

int LLVMFuzzerTestOneInput_159(const uint8_t *Data, size_t Size) {
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

    hid_t dset_id1 = H5Dopen2(file_id1, "dataset1", H5P_DEFAULT);
    hid_t dset_id2 = H5Dopen2(file_id2, "dataset2", H5P_DEFAULT);

    hsize_t nchunks;
    H5Dget_num_chunks(dset_id1, H5S_ALL, &nchunks);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dget_num_chunks to H5Aget_name_by_idx
    hid_t ret_H5Aget_create_plist_zshzs = H5Aget_create_plist(0);
    int ret_H5Aget_num_attrs_kuheu = H5Aget_num_attrs(file_id2);
    if (ret_H5Aget_num_attrs_kuheu < 0){
    	return 0;
    }
    hid_t ret_H5Dget_type_oxlah = H5Dget_type(file_id1);
    const char hybjsprg[1024] = "rcvej";

    ssize_t ret_H5Aget_name_by_idx_ycjls = H5Aget_name_by_idx(ret_H5Aget_create_plist_zshzs, hybjsprg, 0, 0, nchunks, NULL, (size_t )ret_H5Aget_num_attrs_kuheu, ret_H5Dget_type_oxlah);

    // End mutation: Producer.APPEND_MUTATOR

    H5Dget_num_chunks(dset_id2, H5S_ALL, &nchunks);

    hsize_t offset[1] = {0};
    unsigned filter_mask;
    haddr_t addr;
    hsize_t size;


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of H5Dget_chunk_info
    unsigned int eelcpjdz = 0;
    H5Dget_chunk_info(dset_id1, H5S_ALL, 0, offset, &eelcpjdz, &addr, &size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    H5Dget_chunk_info(dset_id2, H5S_ALL, 0, offset, &filter_mask, &addr, &size);

    H5Dget_chunk_info_by_coord(dset_id1, offset, &filter_mask, &addr, &size);
    H5Dget_chunk_info_by_coord(dset_id2, offset, &filter_mask, &addr, &size);

    H5Dchunk_iter(dset_id1, H5P_DEFAULT, dummy_chunk_iter_cb, NULL);
    H5Dchunk_iter(dset_id2, H5P_DEFAULT, dummy_chunk_iter_cb, NULL);

    H5Dclose(dset_id1);
    H5Dclose(dset_id2);

    H5Fclose(file_id1);
    H5Fclose(file_id2);

    H5Fdelete("./dummy_file", H5P_DEFAULT);
    H5Fdelete("./dummy_file", H5P_DEFAULT);

    H5Dclose(dset_id1);
    H5Dclose(dset_id2);

    H5Fclose(file_id1);

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function H5Fclose with H5Dformat_convert
    H5Dformat_convert(file_id2);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}