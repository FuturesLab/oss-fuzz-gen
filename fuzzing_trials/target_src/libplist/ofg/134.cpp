#include <stdint.h>
#include <stddef.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    // Call the function-under-test
    plist_t dict = plist_new_dict();

    // Normally, you would use the `data` and `size` to manipulate or test the `dict`,
    // but since `plist_new_dict()` does not take any parameters, we just call it here.

    // Clean up the plist object to avoid memory leaks
    if (dict != NULL) {
        plist_free(dict);
    }

    return 0;
}