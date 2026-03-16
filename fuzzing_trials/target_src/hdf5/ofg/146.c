#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a file access property list
    hid_t fapl_id = H5Pcreate(H5P_FILE_ACCESS);
    if (fapl_id < 0) {
        return 0;
    }

    // Create a file using the property list
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, fapl_id);
    if (file_id < 0) {
        H5Pclose(fapl_id);
        return 0;
    }

    // Prepare a pointer to hold the VFD handle
    void *vfd_handle = NULL;

    // Call the function-under-test
    herr_t status = H5Fget_vfd_handle(file_id, fapl_id, &vfd_handle);

    // Clean up
    H5Fclose(file_id);
    H5Pclose(fapl_id);

    // Close HDF5 library
    H5close();

    return 0;
}