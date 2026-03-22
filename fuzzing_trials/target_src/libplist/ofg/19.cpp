#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    // Ensure there's enough data to work with
    if (size < 2) {
        return 0;
    }

    // Create two plist objects
    plist_t source_dict = plist_new_dict();
    plist_t dest_dict = plist_new_dict();

    // Extract two null-terminated strings from the data
    const char *key1 = reinterpret_cast<const char *>(data);
    const char *key2 = reinterpret_cast<const char *>(data + size / 2);

    // Ensure strings are null-terminated
    char *key1_dup = strndup(key1, size / 2);
    char *key2_dup = strndup(key2, size / 2);

    // Call the function-under-test
    plist_dict_copy_uint(source_dict, dest_dict, key1_dup, key2_dup);

    // Clean up
    free(key1_dup);
    free(key2_dup);
    plist_free(source_dict);
    plist_free(dest_dict);

    return 0;
}