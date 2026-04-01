#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_207(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t file_id = H5I_INVALID_HID;
    hid_t attr_id = H5I_INVALID_HID;
    char attr_name[256];

    // Ensure that the data size is sufficient for a null-terminated string
    if (size < 1 || size >= sizeof(attr_name)) {
        return 0;
    }

    // Copy data to attr_name and null-terminate it
    memcpy(attr_name, data, size);
    attr_name[size] = '\0';

    // Open a file to obtain a valid hid_t (file_id)
    file_id = H5Fopen("test.h5", H5F_ACC_RDONLY, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Call the function-under-test
    attr_id = H5Aopen_name(file_id, attr_name);

    // Close the attribute if it was successfully opened
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }

    // Close the file
    H5Fclose(file_id);

    return 0;
}