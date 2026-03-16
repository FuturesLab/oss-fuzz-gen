#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "hdf5.h"

// Function to create a simple dataset for testing
hid_t create_test_dataset() {
    hid_t file_id, dataset_id, dataspace_id, dcpl_id;
    hsize_t dims[1] = {10}; // Example dimension size
    hsize_t chunk_dims[1] = {5}; // Example chunk size
    int data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // Example data

    // Create a new file using the default properties
    file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Create the data space for the dataset
    dataspace_id = H5Screate_simple(1, dims, NULL);

    // Create a dataset creation property list and set it to use chunking
    dcpl_id = H5Pcreate(H5P_DATASET_CREATE);
    H5Pset_chunk(dcpl_id, 1, chunk_dims);

    // Create the dataset with chunked storage
    dataset_id = H5Dcreate2(file_id, "/dset", H5T_NATIVE_INT, dataspace_id, 
                            H5P_DEFAULT, dcpl_id, H5P_DEFAULT);

    // Write the initial data to the dataset
    H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);

    // Close the dataspace, property list, and file
    H5Sclose(dataspace_id);
    H5Pclose(dcpl_id);
    H5Fclose(file_id);

    return dataset_id;
}

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Create a test dataset
    hid_t dataset_id = create_test_dataset();
    hid_t dxpl_id = H5Pcreate(H5P_DATASET_XFER); // Create a data transfer property list

    // Ensure there's enough data to read for hsize_t array
    if (size < sizeof(hsize_t)) {
        H5Dclose(dataset_id);
        H5Pclose(dxpl_id);
        return 0;
    }

    // Use the first part of data as hsize_t array
    hsize_t offset[1] = {0}; // Initialize to a valid offset
    if (size >= sizeof(hsize_t)) {
        memcpy(offset, data, sizeof(hsize_t));
        offset[0] %= 10; // Ensure offset is within dataset bounds
    }

    // Use the next part of data as a uint32_t filter mask
    uint32_t filter_mask = 0;
    if (size >= sizeof(hsize_t) + sizeof(uint32_t)) {
        filter_mask = *(uint32_t *)(data + sizeof(hsize_t));
    }

    // Allocate a buffer for the chunk data
    void *chunk_data = malloc(5 * sizeof(int)); // Allocate space for one chunk
    if (chunk_data == NULL) {
        H5Dclose(dataset_id);
        H5Pclose(dxpl_id);
        return 0;
    }

    // Set buffer size
    size_t buf_size = 5 * sizeof(int);

    // Call the function-under-test with the correct number of arguments
    herr_t result = H5Dread_chunk2(dataset_id, dxpl_id, offset, &filter_mask, chunk_data, &buf_size);

    // Check for errors in reading the chunk
    if (result < 0) {
        // Handle the error if needed
    }

    // Free allocated memory and close HDF5 resources
    free(chunk_data);
    H5Dclose(dataset_id);
    H5Pclose(dxpl_id);

    return 0;
}