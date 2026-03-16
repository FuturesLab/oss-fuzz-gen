#include <stdint.h>
#include "hdf5.h"
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a temporary file to work with
    hid_t file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Failed to create a file, exit early
    }

    // Use the input data to create a dataset
    if (size > 0) {
        // Ensure the input data is not null and has meaningful content
        uint8_t *non_null_data = malloc(size);
        if (non_null_data == NULL) {
            H5Fclose(file_id);
            H5close();
            return 0;
        }
        memcpy(non_null_data, data, size);

        hsize_t dims[1] = {size};
        hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
        if (dataspace_id >= 0) {
            hid_t dataset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_UINT8, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
            if (dataset_id >= 0) {
                // Write the input data to the dataset
                H5Dwrite(dataset_id, H5T_NATIVE_UINT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, non_null_data);

                // Read the data back
                uint8_t *read_data = malloc(size);
                if (read_data != NULL) {
                    H5Dread(dataset_id, H5T_NATIVE_UINT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, read_data);

                    // Modify the data (e.g., invert all bytes)
                    for (size_t i = 0; i < size; i++) {
                        read_data[i] = ~read_data[i];
                    }

                    // Write the modified data back to the dataset
                    H5Dwrite(dataset_id, H5T_NATIVE_UINT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, read_data);

                    free(read_data);
                }

                // Optionally, delete the dataset
                H5Ldelete(file_id, "dataset", H5P_DEFAULT);

                H5Dclose(dataset_id);
            }
            H5Sclose(dataspace_id);
        }

        free(non_null_data);
    }

    // Close the file
    herr_t status = H5Fclose(file_id);

    // Check the status (optional, just to ensure it was closed properly)
    if (status < 0) {
        // Handle error if needed
    }

    // Clean up: close the HDF5 library
    H5close();

    return 0;
}