#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    hid_t dataset_id;
    hid_t access_plist_id;

    // Ensure that the input size is sufficient to form a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Interpret the input data as an hid_t
    dataset_id = *(const hid_t *)data;

    // Call the function-under-test
    access_plist_id = H5Dget_access_plist(dataset_id);

    // Normally, you would perform some checks or operations with access_plist_id
    // For fuzzing purposes, we just ensure the function is called

    // Close the property list if it was successfully created
    if (access_plist_id >= 0) {
        H5Pclose(access_plist_id);
    }

    return 0;
}