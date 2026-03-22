extern "C" {
    #include <plist/plist.h>
    #include <stdlib.h>
    #include <string.h>
}

extern "C" int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *input_string = (char *)malloc(size + 1);
    if (input_string == NULL) {
        return 0;
    }
    memcpy(input_string, data, size);
    input_string[size] = '\0';

    // Attempt to parse the input string as a plist
    plist_t root_node = NULL;
    plist_from_xml(input_string, size, &root_node);

    if (root_node) {
        // Perform operations on the plist node to increase coverage
        plist_t node = plist_dict_get_item(root_node, "key");
        if (node) {
            char *retrieved_string = NULL;
            plist_get_string_val(node, &retrieved_string);

            if (retrieved_string) {
                // Further operations can be added here to explore more code paths
                free(retrieved_string);
            }
        }

        // Free the plist structure
        plist_free(root_node);
    }

    // Clean up
    free(input_string);

    return 0;
}