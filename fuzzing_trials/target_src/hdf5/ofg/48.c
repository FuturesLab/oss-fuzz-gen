#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>
#include <string.h>

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t loc_id = H5I_INVALID_HID; // Invalid handle ID for testing
    const char *name = "test_object"; // A test object name
    size_t bufsize = 256; // Size of the buffer for the comment
    char comment[256]; // Buffer to store the comment

    // Ensure that the data is not null and has a minimum size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Copy the input data into the comment buffer, ensuring it is null-terminated
    size_t copy_size = size < bufsize - 1 ? size : bufsize - 1;
    memcpy(comment, data, copy_size);
    comment[copy_size] = '\0';

    // Call the function-under-test
    int result = H5Gget_comment(loc_id, name, bufsize, comment);

    // Return 0 to indicate successful execution
    return 0;
}