#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Initialize the HDF5 library
    H5open();

    // Create a memory file to avoid file I/O
    hid_t fapl = H5Pcreate(H5P_FILE_ACCESS);
    H5Pset_fapl_core(fapl, (size_t)1024, 0);

    // Create a new HDF5 file using the core file driver
    hid_t file_id = H5Fcreate("fuzz_test_file", H5F_ACC_TRUNC, H5P_DEFAULT, fapl);

    // Create a dataspace
    hsize_t dims[1] = {10}; // Example dimension
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);

    // Create a dataset
    hid_t dataset_id = H5Dcreate2(file_id, "dset", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Utilize the input data
    if (size >= sizeof(int) * 10) {
        // Write the input data to the dataset if size is sufficient
        H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
    }

    // Call the function-under-test
    haddr_t offset = H5Dget_offset(dataset_id);

    // Clean up
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);
    H5Pclose(fapl);

    // Close the HDF5 library
    H5close();

    return 0;
}