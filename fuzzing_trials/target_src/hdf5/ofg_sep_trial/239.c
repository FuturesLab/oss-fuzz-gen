#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_239(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for our needs
    if (size < 3) {
        return 0;
    }

    // Initialize parameters for H5Fcreate
    const char *filename = "fuzz_test_file.h5";
    unsigned int flags = (unsigned int)data[0]; // Use first byte as flags
    hid_t create_plist = H5P_DEFAULT; // Default property list
    hid_t access_plist = H5P_DEFAULT; // Default property list

    // Call the function-under-test
    hid_t file_id = H5Fcreate(filename, flags, create_plist, access_plist);

    // Close the file if it was successfully created
    if (file_id >= 0) {
        H5Fclose(file_id);
    }

    return 0;
}