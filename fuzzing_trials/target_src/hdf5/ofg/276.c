#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_276(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t file_id = -1; // Default invalid ID
    H5F_scope_t scope = H5F_SCOPE_GLOBAL; // Default scope

    // Ensure size is sufficient for our needs
    if (size < sizeof(hid_t) + sizeof(H5F_scope_t)) {
        return 0;
    }

    // Extract values from data
    file_id = *(const hid_t *)data;
    scope = *(const H5F_scope_t *)(data + sizeof(hid_t));

    // Call the function-under-test
    H5Fflush(file_id, scope);

    return 0;
}