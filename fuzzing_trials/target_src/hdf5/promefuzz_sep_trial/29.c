// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Dget_chunk_index_type at H5D.c:2177:1 in H5Dpublic.h
// H5Dget_num_chunks at H5D.c:2268:1 in H5Dpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Dget_num_chunks at H5D.c:2268:1 in H5Dpublic.h
// H5Dget_chunk_info at H5D.c:2317:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Spublic.h"
#include "H5Tpublic.h"
#include "H5Ppublic.h"

static void write_dummy_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file) {
        fprintf(file, "dummy data");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    const char *filename = "./dummy_file";
    hid_t file_id, dset_id, space_id, type_id;
    herr_t status;
    hsize_t dims[2] = {10, 10};
    hsize_t nchunks;
    H5D_chunk_index_t idx_type;

    // Prepare dummy file
    write_dummy_file(filename);

    // Open file
    file_id = H5Fopen(filename, H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Create dataspace
    space_id = H5Screate_simple(2, dims, NULL);
    if (space_id < 0) goto cleanup_file;

    // Create datatype
    type_id = H5Tcopy(H5T_NATIVE_INT);
    if (type_id < 0) goto cleanup_space;

    // Create dataset
    dset_id = H5Dcreate2(file_id, "dset", type_id, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) goto cleanup_type;

    // Close dataset
    status = H5Dclose(dset_id);
    if (status < 0) goto cleanup_type;

    // Open dataset
    dset_id = H5Dopen2(file_id, "dset", H5P_DEFAULT);
    if (dset_id < 0) goto cleanup_type;

    // Get chunk index type
    status = H5Dget_chunk_index_type(dset_id, &idx_type);
    if (status < 0) goto cleanup_dset;

    // Get number of chunks
    status = H5Dget_num_chunks(dset_id, H5S_ALL, &nchunks);
    if (status < 0) goto cleanup_dset;

    // Write data to dataset
    int buf[10][10] = {0};
    status = H5Dwrite(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);
    if (status < 0) goto cleanup_dset;

    // Get number of chunks again
    status = H5Dget_num_chunks(dset_id, H5S_ALL, &nchunks);
    if (status < 0) goto cleanup_dset;

    // Get chunk info
    hsize_t offset[2];
    unsigned filter_mask;
    haddr_t addr;
    hsize_t size;
    status = H5Dget_chunk_info(dset_id, H5S_ALL, 0, offset, &filter_mask, &addr, &size);
    if (status < 0) goto cleanup_dset;

cleanup_dset:
    H5Dclose(dset_id);
cleanup_type:
    H5Tclose(type_id);
cleanup_space:
    H5Sclose(space_id);
cleanup_file:
    H5Fclose(file_id);

    return 0;
}