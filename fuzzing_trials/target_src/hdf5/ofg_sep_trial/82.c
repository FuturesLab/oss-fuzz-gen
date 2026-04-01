#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    // Declare and initialize the parameters for H5Aexists_by_name
    hid_t loc_id = H5P_DEFAULT; // Use a default property list identifier
    hid_t lapl_id = H5P_DEFAULT; // Use a default link access property list identifier

    // Ensure the size is sufficient for at least two null-terminated strings
    if (size < 2) {
        return 0;
    }

    // Find the position of the first null terminator for the first string
    size_t name1_len = 0;
    while (name1_len < size && data[name1_len] != '\0') {
        name1_len++;
    }

    // If no null terminator is found, return
    if (name1_len == size) {
        return 0;
    }

    // Move past the first null terminator
    name1_len++;

    // Find the position of the second null terminator for the second string
    size_t name2_len = name1_len;
    while (name2_len < size && data[name2_len] != '\0') {
        name2_len++;
    }

    // If no second null terminator is found, return
    if (name2_len == size) {
        return 0;
    }

    // Extract the first and second strings
    const char *obj_name = (const char *)data;
    const char *attr_name = (const char *)(data + name1_len);

    // Call the function-under-test
    htri_t result = H5Aexists_by_name(loc_id, obj_name, attr_name, lapl_id);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}