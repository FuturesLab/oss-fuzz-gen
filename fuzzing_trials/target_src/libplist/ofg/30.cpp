#include <stdint.h>
#include <stddef.h>
#include <plist/plist.h>
#include <string.h>

extern "C" {
    // Include necessary C headers and function signatures
    plist_err_t plist_dict_copy_bool(plist_t, plist_t, const char *, const char *);
}

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    plist_t source_dict = plist_new_dict();
    plist_t dest_dict = plist_new_dict();
    const char *source_key = "source_key";
    const char *dest_key = "dest_key";

    // Ensure the data is not empty before using it
    if (size > 0) {
        // Use the first byte of data to determine a boolean value
        bool value = data[0] % 2 == 0;

        // Add a boolean value to the source dictionary
        plist_dict_set_item(source_dict, source_key, plist_new_bool(value));

        // Use additional bytes from data to create more entries
        for (size_t i = 1; i < size; ++i) {
            char key[16];
            snprintf(key, sizeof(key), "key_%zu", i);
            bool additional_value = data[i] % 2 == 0;
            plist_dict_set_item(source_dict, key, plist_new_bool(additional_value));
        }

        // Call the function-under-test
        plist_dict_copy_bool(source_dict, dest_dict, source_key, dest_key);

        // Retrieve the copied value to ensure the function was effective
        plist_t copied_value = plist_dict_get_item(dest_dict, dest_key);

        // Check if the copied value matches the original
        if (copied_value) {
            uint8_t bool_value = 0;
            plist_get_bool_val(copied_value, &bool_value);
            if (bool_value != value) {
                // Handle the error case where the values do not match
                plist_free(source_dict);
                plist_free(dest_dict);
                return 1; // Return non-zero to indicate an issue
            }
        } else {
            // Handle the case where the item was not copied
            plist_free(source_dict);
            plist_free(dest_dict);
            return 1; // Return non-zero to indicate an issue
        }
    } else {
        // Add a default boolean value to the source dictionary when data is empty
        plist_dict_set_item(source_dict, source_key, plist_new_bool(false));
        
        // Call the function-under-test with default values
        plist_dict_copy_bool(source_dict, dest_dict, source_key, dest_key);

        // Retrieve the copied value to ensure the function was effective
        plist_t copied_value = plist_dict_get_item(dest_dict, dest_key);

        // Check if the copied value matches the default
        if (copied_value) {
            uint8_t bool_value = 0;
            plist_get_bool_val(copied_value, &bool_value);
            if (bool_value != false) {
                // Handle the error case where the values do not match
                plist_free(source_dict);
                plist_free(dest_dict);
                return 1; // Return non-zero to indicate an issue
            }
        } else {
            // Handle the case where the item was not copied
            plist_free(source_dict);
            plist_free(dest_dict);
            return 1; // Return non-zero to indicate an issue
        }
    }

    // Free allocated plist dictionaries
    plist_free(source_dict);
    plist_free(dest_dict);

    return 0;
}