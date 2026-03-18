#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_172(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char filename[size + 1];
    for (size_t i = 0; i < size; i++) {
        filename[i] = (char)data[i];
    }
    filename[size] = '\0';

    // Use a valid file access property list identifier
    hid_t fapl_id = H5Pcreate(H5P_FILE_ACCESS);
    if (fapl_id < 0) {
        return 0; // Failed to create property list, exit
    }

    // Call the function-under-test
    H5Fdelete(filename, fapl_id);

    // Close the property list
    H5Pclose(fapl_id);

    return 0;
}