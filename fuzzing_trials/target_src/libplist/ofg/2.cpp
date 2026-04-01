extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Ensure the data is not NULL and size is greater than 0
    if (data != nullptr && size > 0) {
        plist_t plist = nullptr;
        plist_format_t format;

        // Parse the input data into a plist, providing the required format argument
        plist_from_memory((const char*)data, size, &plist, &format);

        if (plist != nullptr) {
            // Call the function-under-test with the plist
            // Assuming plist_compare_node_value is a hypothetical function
            // If this function does not exist, replace it with an actual function from the plist library
            int result = plist_compare_node_value(plist, plist); // Example function call

            // Free the plist to avoid memory leaks
            plist_free(plist);
        }
    }

    return 0;
}