#include <stdint.h>
#include <stdlib.h>
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Initialize two plist objects
    plist_t plist1 = plist_new_dict();
    plist_t plist2 = plist_new_dict();

    // Populate plist1 with some data
    plist_dict_set_item(plist1, "key1", plist_new_string("value1"));
    plist_dict_set_item(plist1, "key2", plist_new_uint(size));

    // Populate plist2 with some data
    plist_dict_set_item(plist2, "key2", plist_new_string("value2"));
    plist_dict_set_item(plist2, "key3", plist_new_bool(data[0] % 2 == 0));

    // Call the function-under-test
    plist_dict_merge(&plist1, plist2);

    // Clean up
    plist_free(plist1);
    plist_free(plist2);

    return 0;
}