#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    // Define and initialize the parameters for plist_dict_copy_string
    plist_t source_dict = NULL;
    plist_t dest_dict = NULL;
    const char *source_key = "source_key";
    const char *dest_key = "dest_key";

    // Ensure data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a plist dictionary for source and destination
    source_dict = plist_new_dict();
    dest_dict = plist_new_dict();

    // Add a string to the source dictionary using the source_key
    char *value = (char *)malloc(size + 1);
    if (value == NULL) {
        plist_free(source_dict);
        plist_free(dest_dict);
        return 0;
    }
    memcpy(value, data, size);
    value[size] = '\0';
    plist_dict_set_item(source_dict, source_key, plist_new_string(value));

    // Call the function-under-test
    plist_err_t result = plist_dict_copy_string(source_dict, dest_dict, source_key, dest_key);

    // Clean up
    free(value);
    plist_free(source_dict);
    plist_free(dest_dict);

    return 0;
}