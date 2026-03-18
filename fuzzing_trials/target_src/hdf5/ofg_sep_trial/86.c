#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    hid_t dataset_id = H5I_INVALID_HID;
    hid_t mem_type_id = H5T_NATIVE_INT;  // Assuming integer data type
    hid_t mem_space_id = H5S_ALL;        // Entire dataset
    hid_t file_space_id = H5S_ALL;       // Entire dataset
    hid_t plist_id = H5P_DEFAULT;        // Default property list
    int buffer[10];                      // Buffer to hold data

    // Ensure data is not NULL and size is sufficient
    if (data == NULL || size < sizeof(int) * 10) {
        return 0;
    }

    // Simulate dataset_id assignment (in real scenarios, it should be a valid dataset)
    dataset_id = *((hid_t *)data);

    // Call the function-under-test
    herr_t status = H5Dread(dataset_id, mem_type_id, mem_space_id, file_space_id, plist_id, buffer);

    // Handle status if needed (for fuzzing, we just return 0)
    return 0;
}