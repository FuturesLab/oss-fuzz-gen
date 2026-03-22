#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" {
    int plist_int_val_is_negative(plist_t node);
}

extern "C" int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    if (size < sizeof(int64_t)) {
        return 0;
    }

    plist_t node = plist_new_int(*(int64_t*)data);

    // Call the function-under-test
    int result = plist_int_val_is_negative(node);

    // Clean up
    plist_free(node);

    return 0;
}