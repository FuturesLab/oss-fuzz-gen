#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Ensure the size is sufficient to form a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t value from the input data
    hid_t file_id = *((hid_t *)data);

    // Call the function-under-test
    hid_t access_plist_id = H5Fget_access_plist(file_id);

    // Close the access property list if it is valid
    if (access_plist_id >= 0) {
        H5Pclose(access_plist_id);
    }

    // Close HDF5 library
    H5close();

    return 0;
}