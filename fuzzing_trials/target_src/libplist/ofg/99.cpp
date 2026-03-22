extern "C" {
    #include <plist/plist.h>
    #include <stdlib.h> // Include the standard library for 'free'
}

extern "C" int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    // Initialize a plist from the input data
    plist_t plist = NULL;
    if (size > 0) {
        plist_from_bin((const char*)data, size, &plist);
    }

    // Ensure plist is not NULL
    if (plist == NULL) {
        plist = plist_new_array();
    }

    // Try different index values to get items from the plist array
    uint32_t indices[] = {0, 1, 2, 3, 4, 5, 10, 100, 1000};
    size_t num_indices = sizeof(indices) / sizeof(indices[0]);

    for (size_t i = 0; i < num_indices; ++i) {
        uint32_t index = indices[i];
        plist_t item = plist_array_get_item(plist, index);
        
        // Do something with the item to ensure it's accessed
        if (item != NULL) {
            char *xml = NULL;
            uint32_t length = 0;
            plist_to_xml(item, &xml, &length);
            if (xml) {
                free(xml);
            }
        }
    }

    // Free the plist
    plist_free(plist);

    return 0;
}