#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_183(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to extract necessary parameters
    if (size < 10) {
        return 0;
    }

    // Extracting parameters from the input data
    const char *file_name = "test_file.h5"; // Fixed non-NULL file name
    unsigned int flags = (unsigned int)data[0];
    hid_t fcpl = H5Pcreate(H5P_FILE_CREATE);
    hid_t fapl = H5Pcreate(H5P_FILE_ACCESS);

    // Call the function-under-test
    hid_t file_id = H5Fcreate(file_name, flags, fcpl, fapl);

    // Close the file if it was successfully created
    if (file_id >= 0) {
        H5Fclose(file_id);
    }

    // Close property lists
    H5Pclose(fcpl);
    H5Pclose(fapl);

    return 0;
}