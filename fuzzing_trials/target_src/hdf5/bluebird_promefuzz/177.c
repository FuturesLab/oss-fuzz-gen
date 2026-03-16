#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hdf5.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        const char *dummy_content = "This is a dummy file for HDF5 testing.";
        fwrite(dummy_content, 1, strlen(dummy_content), file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_177(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    } // Ensure there is at least some data.

    write_dummy_file();

    hid_t file_id, plist_id, dset_id1, dset_id2;
    herr_t status;
    hid_t space_id, type_id;
    hsize_t dims[1] = {10};
    int data[10] = {0}; // Dummy data buffer

    // Create a new file using default properties.
    file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Get the file access property list identifier.
    plist_id = H5Fget_access_plist(file_id);
    if (plist_id < 0) {
        goto close_file;
    }

    // Create a simple dataspace.
    space_id = H5Screate_simple(1, dims, NULL);
    if (space_id < 0) {
        goto close_plist;
    }

    // Create a new dataset within the file using defined dataspace and datatype.
    type_id = H5Tcopy(H5T_NATIVE_INT);
    dset_id1 = H5Dcreate2(file_id, "dset1", type_id, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id1 < 0) {
        goto close_space;
    }

    // Write the dataset.

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dcreate2 to H5Dget_chunk_info

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function H5Fget_create_plist with H5Dget_create_plist
    hid_t ret_H5Fget_create_plist_fdxuc = H5Dget_create_plist(dset_id1);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    hsize_t ret_H5Dget_storage_size_scinq = H5Dget_storage_size(dset_id1);
    hsize_t ret_H5Aget_storage_size_qgvay = H5Aget_storage_size(dset_id1);
    hsize_t yvqdwwmp;
    memset(&yvqdwwmp, 0, sizeof(yvqdwwmp));
    unsigned int deloieqr = 0;

    herr_t ret_H5Dget_chunk_info_vborp = H5Dget_chunk_info(dset_id1, ret_H5Fget_create_plist_fdxuc, ret_H5Dget_storage_size_scinq, &yvqdwwmp, &deloieqr, NULL, &ret_H5Aget_storage_size_qgvay);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of H5Dwrite
    status = H5Dwrite(dset_id1, H5T_NATIVE_INT, H5S_ALL, plist_id, H5P_DEFAULT, data);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (status < 0) {
        goto close_dset1_early;
    }

    // Flush the dataset.
    status = H5Dflush(dset_id1);
    if (status < 0) {
        goto close_dset1_early;
    }

    // Create another dataset.
    dset_id2 = H5Dcreate2(file_id, "dset2", type_id, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id2 < 0) {
        goto close_dset1_early;
    }

    // Close datasets.
    H5Dclose(dset_id1);
    H5Dclose(dset_id2);

    // Close property lists and spaces.
close_space:
    H5Sclose(space_id);
close_plist:
    H5Pclose(plist_id);
close_file:
    H5Fclose(file_id);

    // Reopen the file and datasets for further testing.
    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of H5Dcreate2
    dset_id1 = H5Dcreate2(file_id, "dset3", ret_H5Fget_create_plist_fdxuc, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (dset_id1 >= 0) {
        H5Dclose(dset_id1);
    }

    // Close the file.
    H5Fclose(file_id);

    return 0;

close_dset1_early:
    H5Dclose(dset_id1);
    goto close_space;
}