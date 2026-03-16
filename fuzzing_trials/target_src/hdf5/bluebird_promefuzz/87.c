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

int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size) {
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
    H5Dget_num_chunks(dset_id2, H5S_ALL, &nchunks);

    hsize_t offset[1] = {0};
    unsigned filter_mask;
    haddr_t addr;
    hsize_t size;


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of H5Dget_chunk_info
    H5Dget_chunk_info(dset_id1, H5S_ALL, 0, offset, NULL, &addr, &size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    H5Dget_chunk_info(dset_id2, H5S_ALL, 0, offset, &filter_mask, &addr, &size);

    H5Dget_chunk_info_by_coord(dset_id1, offset, &filter_mask, &addr, &size);
    H5Dget_chunk_info_by_coord(dset_id2, offset, &filter_mask, &addr, &size);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dget_chunk_info_by_coord to H5Fget_name
    hid_t ret_H5Dget_access_plist_iloaj = H5Dget_access_plist(dset_id2);

    ssize_t ret_H5Fget_name_dmuga = H5Fget_name(ret_H5Dget_access_plist_iloaj, (char *)"r", (size_t )filter_mask);

    // End mutation: Producer.APPEND_MUTATOR

    H5Dchunk_iter(dset_id1, H5P_DEFAULT, dummy_chunk_iter_cb, NULL);
    H5Dchunk_iter(dset_id2, H5P_DEFAULT, dummy_chunk_iter_cb, NULL);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function H5Dclose with H5Dflush
    H5Dflush(dset_id1);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    H5Dclose(dset_id2);

    H5Fclose(file_id1);
    H5Fclose(file_id2);

    H5Fdelete("./dummy_file", H5P_DEFAULT);
    H5Fdelete("./dummy_file", H5P_DEFAULT);

    H5Dclose(dset_id1);
    H5Dclose(dset_id2);

    H5Fclose(file_id1);
    H5Fclose(file_id2);

    return 0;
}