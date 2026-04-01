#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_254(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t file_id, dataspace_id, datatype_id, dcpl_id, dapl_id;
    hid_t dataset_id;

    // Initialize the HDF5 library
    H5open();

    // Create a new file using the default properties.
    file_id = H5Fcreate("fuzz_test_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Create a simple dataspace with a single dimension
    hsize_t dims[1] = {size / sizeof(int)};
    dataspace_id = H5Screate_simple(1, dims, NULL);

    // Create a datatype
    datatype_id = H5Tcopy(H5T_NATIVE_INT);
    H5Tset_order(datatype_id, H5T_ORDER_LE);

    // Create property lists (using default properties for simplicity)
    dcpl_id = H5Pcreate(H5P_DATASET_CREATE);
    dapl_id = H5Pcreate(H5P_DATASET_ACCESS);

    // Call the function under test
    dataset_id = H5Dcreate_anon(file_id, datatype_id, dataspace_id, dcpl_id, dapl_id);

    // Write the input data to the dataset
    if (dims[0] > 0) {
        H5Dwrite(dataset_id, datatype_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
    }

    // Close the dataset and other resources
    H5Dclose(dataset_id);
    H5Pclose(dcpl_id);
    H5Pclose(dapl_id);
    H5Tclose(datatype_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    // Close the HDF5 library
    H5close();

    return 0;
}