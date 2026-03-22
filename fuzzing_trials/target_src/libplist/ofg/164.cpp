extern "C" {
    #include <stdint.h>
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for the function parameters
    if (size < 4) {
        return 0;
    }

    // Initialize the parameters for plist_from_memory
    const char *memory = reinterpret_cast<const char*>(data);
    uint32_t memory_size = static_cast<uint32_t>(size);
    plist_t plist = nullptr;
    plist_format_t format = PLIST_FORMAT_XML; // Assuming XML format for initialization

    // Call the function-under-test
    plist_err_t result = plist_from_memory(memory, memory_size, &plist, &format);

    // Clean up if plist was created
    if (plist != nullptr) {
        plist_free(plist);
    }

    return 0;
}