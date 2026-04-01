#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Declare and initialize the hid_t variable
    hid_t dataset_id;
    hid_t access_plist_id;

    // Ensure size is sufficient for creating a valid dataset_id
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Copy the data into the dataset_id
    dataset_id = *((hid_t *)data);

    // Call the function-under-test
    access_plist_id = H5Dget_access_plist(dataset_id);

    // Close the access property list if it was successfully created
    if (access_plist_id >= 0) {
        H5Pclose(access_plist_id);
    }

    return 0;
}