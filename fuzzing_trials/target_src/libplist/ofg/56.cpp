extern "C" {
    #include <plist/plist.h>
    #include <stdlib.h>  // Include the standard library for the free function
}

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize a plist node
    plist_t node = plist_new_data((const char*)data, (uint32_t)size);

    if (!node) {
        return 0;
    }

    // Call the function-under-test
    plist_t copied_node = plist_copy(node);

    // Perform additional operations to increase code coverage
    if (copied_node) {
        char* xml = nullptr;
        uint32_t xml_size = 0;
        plist_to_xml(copied_node, &xml, &xml_size);
        if (xml) {
            free(xml);
        }
    }

    // Cleanup
    plist_free(node);
    plist_free(copied_node);

    return 0;
}