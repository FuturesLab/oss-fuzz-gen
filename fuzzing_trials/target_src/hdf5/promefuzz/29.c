// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
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
#include <H5Dpublic.h>
#include <H5Fpublic.h>
#include <H5Ppublic.h>
#include <H5Tpublic.h>
#include <H5Spublic.h>

#define DUMMY_FILE "./dummy_file"
#define DATASET_NAME "test_dataset"

static void prepare_dummy_file() {
    FILE *file = fopen(DUMMY_FILE, "wb");
    if (file) {
        char data[1024] = {0};
        fwrite(data, 1, 1024, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    // Prepare the dummy file
    prepare_dummy_file();

    // Open the file
    hid_t file_id = H5Fopen(DUMMY_FILE, H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Create a dataspace
    hid_t dataspace_id = H5Screate(H5S_SCALAR);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Create a dataset
    hid_t dset_id = H5Dcreate2(file_id, DATASET_NAME, H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0;
    }

    // Close the dataset
    H5Dclose(dset_id);

    // Open the dataset
    dset_id = H5Dopen2(file_id, DATASET_NAME, H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0;
    }

    // Get chunk index type
    H5D_chunk_index_t idx_type;
    H5Dget_chunk_index_type(dset_id, &idx_type);

    // Get number of chunks
    hsize_t nchunks;
    H5Dget_num_chunks(dset_id, H5S_ALL, &nchunks);

    // Write data to the dataset
    int data = 0;
    H5Dwrite(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, &data);

    // Get number of chunks again
    H5Dget_num_chunks(dset_id, H5S_ALL, &nchunks);

    // Get chunk info
    hsize_t offset;
    unsigned filter_mask;
    haddr_t addr;
    hsize_t size;
    H5Dget_chunk_info(dset_id, H5S_ALL, 0, &offset, &filter_mask, &addr, &size);

    // Close the dataset
    H5Dclose(dset_id);

    // Close the dataspace
    H5Sclose(dataspace_id);

    // Close the file
    H5Fclose(file_id);

    return 0;
}