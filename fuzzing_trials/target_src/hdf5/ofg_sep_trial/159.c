#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    // Initialize the HDF5 library
    H5open();

    // Create a file and a dataset to use for testing
    hid_t file_id = H5Fcreate("fuzz_test_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    hsize_t dims[1] = {10};
    hid_t space_id = H5Screate_simple(1, dims, NULL);
    if (space_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    hid_t dset_id = H5Dcreate2(file_id, "fuzz_test_dataset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    // Use the input data to write to the dataset if size is sufficient
    if (size >= 10 * sizeof(int)) {
        herr_t write_status = H5Dwrite(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
        if (write_status < 0) {
            H5Dclose(dset_id);
            H5Sclose(space_id);
            H5Fclose(file_id);
            H5close();
            return 0;
        }
    }

    // Call the function-under-test
    herr_t status = H5Dflush(dset_id);

    // Clean up
    H5Dclose(dset_id);
    H5Sclose(space_id);
    H5Fclose(file_id);
    H5close();

    return 0;
}