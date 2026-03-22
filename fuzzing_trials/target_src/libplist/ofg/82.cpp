#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    // Call the function-under-test
    plist_t plist = plist_new_null();

    // Clean up the plist object
    plist_free(plist);

    return 0;
}