#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <plist/plist.h>

extern "C" {
    plist_err_t plist_dict_copy_uint(plist_t, plist_t, const char *, const char *);
}

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Ensure there is enough data for the keys
    if (size < 4) return 0; // Adjusted to ensure we have enough data for two keys

    // Initialize plist variables
    plist_t src_dict = plist_new_dict();
    plist_t dest_dict = plist_new_dict();

    // Create keys from the input data
    size_t key1_len = data[0] % (size - 2) + 1; // Ensure non-zero length and enough space for key2
    size_t key2_len = data[1] % (size - key1_len - 1) + 1; // Ensure non-zero length and enough space for key2

    if (key1_len + key2_len + 2 > size) return 0; // Ensure we do not read beyond the buffer

    char key1[key1_len + 1];
    char key2[key2_len + 1];

    // Ensure the keys are null-terminated
    memcpy(key1, data + 2, key1_len);
    key1[key1_len] = '\0';

    memcpy(key2, data + 2 + key1_len, key2_len);
    key2[key2_len] = '\0';

    // Add some integer values to the source dictionary
    plist_dict_set_item(src_dict, key1, plist_new_uint(42));

    // Call the function under test
    plist_err_t result = plist_dict_copy_uint(dest_dict, src_dict, key1, key2);

    // Cleanup
    plist_free(src_dict);
    plist_free(dest_dict);

    return 0;
}