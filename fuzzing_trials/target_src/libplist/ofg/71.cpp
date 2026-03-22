extern "C" {
    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>
    #include <plist/plist.h> // Assuming plist library is available
}

extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    char *input_data;
    uint64_t length;
    plist_t plist;

    // Ensure the input size is non-zero and manageable
    if (size == 0) {
        return 0;
    }

    // Allocate memory for input_data and copy data
    input_data = (char *)malloc(size + 1);
    if (!input_data) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0'; // Null-terminate the string

    // Set length to the size of the data
    length = (uint64_t)size;

    // Call the function-under-test
    plist = plist_new_data(input_data, length);

    // Check if plist is successfully created
    if (plist != NULL) {
        // Perform additional operations to increase code coverage
        char *xml = NULL;
        uint32_t xml_length = 0;
        plist_to_xml(plist, &xml, &xml_length);
        if (xml) {
            free(xml);
        }

        // Free the plist object
        plist_free(plist);
    }

    // Free allocated memory
    free(input_data);

    return 0;
}