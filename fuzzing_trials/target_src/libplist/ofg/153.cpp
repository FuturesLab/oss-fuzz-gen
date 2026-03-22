extern "C" {
    #include <stdint.h>
    #include <stdlib.h>
    #include <plist/plist.h>

    int plist_date_val_compare(plist_t plist, int32_t sec, int32_t usec);
}

extern "C" int LLVMFuzzerTestOneInput_153(const uint8_t *data, size_t size) {
    if (size < sizeof(int32_t) * 2) {
        return 0; // Not enough data to extract two int32_t values
    }

    // Extract two int32_t values from the input data
    int32_t sec = *(reinterpret_cast<const int32_t*>(data));
    int32_t usec = *(reinterpret_cast<const int32_t*>(data + sizeof(int32_t)));

    // Create a plist object
    plist_t plist = plist_new_date(sec, usec);

    // Call the function-under-test
    int result = plist_date_val_compare(plist, sec, usec);

    // Free the plist object
    plist_free(plist);

    return 0;
}