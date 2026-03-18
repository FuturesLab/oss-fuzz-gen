#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_237(const uint8_t *data, size_t size) {
    // Create a file in memory using the fuzzer input
    hid_t fapl_id = H5Pcreate(H5P_FILE_ACCESS);
    H5Pset_fapl_core(fapl_id, (size_t)512, 0);

    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, fapl_id);

    // Write the fuzzer data to the file
    if (file_id >= 0) {
        hid_t dset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_UINT8, H5Screate_simple(1, &size, NULL), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (dset_id >= 0) {
            H5Dwrite(dset_id, H5T_NATIVE_UINT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
            H5Dclose(dset_id);
        }
        H5Fclose(file_id);
    }

    // Open the file in read-only mode to test the function
    file_id = H5Fopen("testfile.h5", H5F_ACC_RDONLY, H5P_DEFAULT);

    // Check if the file was opened successfully
    if (file_id >= 0) {
        // Close the file to clean up
        H5Fclose(file_id);
    }

    // Close the file access property list
    H5Pclose(fapl_id);

    return 0;
}