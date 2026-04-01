// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dwrite_chunk at H5D.c:1491:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dread_chunk1 at H5Ddeprec.c:350:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dread_chunk1 at H5Ddeprec.c:350:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Spublic.h"
#include "H5Ppublic.h"
#include "H5Tpublic.h"

#define DATASET_NAME "dummy_dataset"
#define DUMMY_FILE "./dummy_file"

static hid_t create_dummy_dataset() {
    hid_t file_id, space_id, dset_id;
    hsize_t dims[2] = {10, 10};

    // Create a new file using default properties.
    file_id = H5Fcreate(DUMMY_FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return -1;

    // Create the data space for the dataset.
    space_id = H5Screate_simple(2, dims, NULL);
    if (space_id < 0) {
        H5Fclose(file_id);
        return -1;
    }

    // Create the dataset with default properties.
    dset_id = H5Dcreate2(file_id, DATASET_NAME, H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    
    // Clean up
    H5Sclose(space_id);
    H5Fclose(file_id);

    return dset_id;
}

int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hsize_t) * 2 + sizeof(uint32_t)) {
        return 0; // Not enough data to proceed
    }

    hid_t dset_id = create_dummy_dataset();
    if (dset_id < 0) return 0;

    hsize_t offset[2];
    memcpy(offset, Data, sizeof(hsize_t) * 2);
    uint32_t filters = *(uint32_t *)(Data + sizeof(hsize_t) * 2);

    // Prepare a buffer for reading and writing
    size_t buf_size = 100;
    void *buf = malloc(buf_size);
    if (!buf) {
        H5Dclose(dset_id);
        return 0;
    }

    // Write a chunk
    herr_t status = H5Dwrite_chunk(dset_id, H5P_DEFAULT, filters, offset, buf_size, buf);
    if (status < 0) {
        free(buf);
        H5Dclose(dset_id);
        return 0;
    }

    // Read a chunk
    status = H5Dread_chunk1(dset_id, H5P_DEFAULT, offset, &filters, buf);
    if (status < 0) {
        free(buf);
        H5Dclose(dset_id);
        return 0;
    }

    // Read a chunk again
    status = H5Dread_chunk1(dset_id, H5P_DEFAULT, offset, &filters, buf);
    
    // Cleanup
    free(buf);
    H5Dclose(dset_id);
    return 0;
}