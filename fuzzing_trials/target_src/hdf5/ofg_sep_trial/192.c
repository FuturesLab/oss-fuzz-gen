#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <hdf5.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_192(const uint8_t *data, size_t size) {
    hid_t dataset_id = H5I_INVALID_HID;
    hid_t mem_type_id = H5T_NATIVE_INT;
    hid_t mem_space_id = H5S_ALL;
    hid_t file_space_id = H5S_ALL;
    hid_t plist_id = H5P_DEFAULT;

    // Ensure the data pointer is not NULL and size is greater than 0
    if (data == NULL || size < sizeof(int)) {
        return 0;
    }

    // Create a simple dataspace
    hsize_t dims[1] = {size / sizeof(int)};
    mem_space_id = H5Screate_simple(1, dims, NULL);
    if (mem_space_id < 0) {
        return 0;
    }

    // Create a dataset for testing
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        H5Sclose(mem_space_id);
        return 0;
    }

    dataset_id = H5Dcreate(file_id, "dataset", mem_type_id, mem_space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Fclose(file_id);
        H5Sclose(mem_space_id);
        return 0;
    }

    // Call the function-under-test
    herr_t status = H5Dwrite(dataset_id, mem_type_id, mem_space_id, file_space_id, plist_id, (const void *)data);
    if (status < 0) {
        // Handle error in writing data
        fprintf(stderr, "Error writing data to dataset\n");
    }

    // Read back the data to ensure it was written correctly
    int *read_data = (int *)malloc(size);
    if (read_data) {
        status = H5Dread(dataset_id, mem_type_id, mem_space_id, file_space_id, plist_id, read_data);
        if (status < 0) {
            fprintf(stderr, "Error reading data from dataset\n");
        }

        // Additional operations to increase code coverage
        // Modify a part of the data
        if (size >= sizeof(int)) {
            read_data[0] = 42;  // Arbitrary modification
            status = H5Dwrite(dataset_id, mem_type_id, mem_space_id, file_space_id, plist_id, read_data);
            if (status < 0) {
                fprintf(stderr, "Error writing modified data to dataset\n");
            }
        }

        // Attempt to read the modified data
        status = H5Dread(dataset_id, mem_type_id, mem_space_id, file_space_id, plist_id, read_data);
        if (status < 0) {
            fprintf(stderr, "Error reading modified data from dataset\n");
        }

        free(read_data);
    }

    // Cleanup
    H5Dclose(dataset_id);
    H5Fclose(file_id);
    H5Sclose(mem_space_id);

    return 0;
}