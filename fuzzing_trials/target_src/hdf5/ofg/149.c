#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    // Initialize the HDF5 library
    H5open();

    // Ensure the size is sufficient for our needs
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract an hid_t value from the data
    hid_t file_id = *((hid_t*)data);

    // Call the function-under-test
    hid_t plist_id = H5Fget_create_plist(file_id);

    // Close the property list if it was successfully created
    if (plist_id >= 0) {
        H5Pclose(plist_id);
    }

    // Close the HDF5 library
    H5close();

    return 0;
}