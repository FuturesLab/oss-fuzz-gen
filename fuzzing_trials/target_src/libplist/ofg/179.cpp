extern "C" {
    #include <plist/plist.h>
}

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_179(const uint8_t *data, size_t size) {
    // Ensure size is at least 1 to avoid empty string
    if (size < 1) return 0;

    // Initialize plist_t from raw data
    plist_t plist = nullptr;
    plist_format_t format = PLIST_FORMAT_XML; // Assume an initial format
    plist_from_memory((const char*)data, size, &plist, &format);

    if (plist) {
        // Perform operations on the plist to increase code coverage
        char *xml = nullptr;
        uint32_t xml_len = 0;
        plist_to_xml(plist, &xml, &xml_len);

        // Clean up
        if (xml) {
            free(xml);
        }
        plist_free(plist);
    }

    return 0;
}