#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    if (size < sizeof(int32_t) * 2) {
        return 0;
    }

    // Extract two int32_t values from the input data
    int32_t sec = *((int32_t*)data);
    int32_t usec = *((int32_t*)(data + sizeof(int32_t)));

    // Call the function-under-test
    plist_t date = plist_new_date(sec, usec);

    // Clean up the created plist object
    if (date != NULL) {
        plist_free(date);
    }

    return 0;
}