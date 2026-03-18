#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_241(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create meaningful inputs
    if (size < 2) return 0;

    // Prepare inputs for H5Fcreate
    const char *filename = "testfile.h5"; // Use a fixed filename for testing
    unsigned int flags = (unsigned int)data[0]; // Use the first byte of data for flags
    hid_t fcpl_id = H5P_DEFAULT; // File creation property list
    hid_t fapl_id = H5P_DEFAULT; // File access property list

    // Call the function-under-test
    hid_t file_id = H5Fcreate(filename, flags, fcpl_id, fapl_id);

    // If the file was successfully created, close it
    if (file_id >= 0) {
        H5Fclose(file_id);
    }

    return 0;
}