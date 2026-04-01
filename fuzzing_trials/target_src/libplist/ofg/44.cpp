#include <stdint.h>
#include <stddef.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Initialize plist
    plist_t plist = plist_new_dict();

    // Ensure the data size is sufficient to extract two int32_t values
    if (size < sizeof(int32_t) * 2) {
        plist_free(plist);
        return 0;
    }

    // Extract two int32_t values from the input data
    int32_t val1 = *reinterpret_cast<const int32_t*>(data);
    int32_t val2 = *reinterpret_cast<const int32_t*>(data + sizeof(int32_t));

    // Call the function-under-test
    plist_set_date_val(plist, val1, val2);

    // Clean up
    plist_free(plist);

    return 0;
}