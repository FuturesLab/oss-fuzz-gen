#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_212(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a valid string
    if (size == 0 || data[size - 1] != '\0') {
        return 0;
    }

    // Use the input data as the filename
    const char *filename = (const char *)data;

    // Create a file access property list
    hid_t fapl_id = H5Pcreate(H5P_FILE_ACCESS);
    if (fapl_id < 0) {
        return 0;
    }

    // Call the function-under-test
    htri_t result = H5Fis_accessible(filename, fapl_id);

    // Close the file access property list
    H5Pclose(fapl_id);

    return 0;
}