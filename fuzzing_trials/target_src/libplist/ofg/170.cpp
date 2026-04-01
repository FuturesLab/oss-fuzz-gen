#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <plist/plist.h>

extern "C" {
    // Function-under-test
    plist_err_t plist_dict_copy_data(plist_t dest, plist_t src, const char *key, const char *new_key);
}

extern "C" int LLVMFuzzerTestOneInput_170(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for two null-terminated strings
    if (size < 4) {
        return 0;
    }

    // Initialize plist objects
    plist_t src = plist_new_dict();
    plist_t dest = plist_new_dict();

    // Extract two null-terminated strings from the data
    size_t key_len = strnlen((const char *)data, size);
    size_t new_key_len = strnlen((const char *)(data + key_len + 1), size - key_len - 1);

    // Ensure both strings are null-terminated within the data
    if (key_len >= size || new_key_len >= size - key_len - 1) {
        plist_free(src);
        plist_free(dest);
        return 0;
    }

    const char *key = (const char *)data;
    const char *new_key = (const char *)(data + key_len + 1);

    // Add a dummy entry to the source plist
    plist_dict_set_item(src, key, plist_new_string("dummy_value"));

    // Call the function-under-test
    plist_err_t result = plist_dict_copy_data(dest, src, key, new_key);

    // Clean up
    plist_free(src);
    plist_free(dest);

    return 0;
}