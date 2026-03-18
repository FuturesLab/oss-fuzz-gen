#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for extracting parameters
    if (size < sizeof(hid_t) + sizeof(unsigned int)) {
        return 0;
    }

    // Extract the parameters from the input data
    hid_t file_id = *((hid_t *)data);
    unsigned int types = *((unsigned int *)(data + sizeof(hid_t)));

    // Call the function-under-test
    ssize_t obj_count = H5Fget_obj_count(file_id, types);

    // Use the result in some way to avoid any compiler optimizations
    if (obj_count < 0) {
        // Handle error case if needed
    }

    return 0;
}