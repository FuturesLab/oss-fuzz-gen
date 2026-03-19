// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_bool at plist.c:469:9 in plist.h
// plist_set_bool_val at plist.c:1593:6 in plist.h
// plist_bool_val_is_true at plist.c:1635:5 in plist.h
// plist_get_bool_val at plist.c:1353:6 in plist.h
// plist_new_dict at plist.c:436:9 in plist.h
// plist_new_dict at plist.c:436:9 in plist.h
// plist_dict_set_item at plist.c:941:6 in plist.h
// plist_new_bool at plist.c:469:9 in plist.h
// plist_dict_set_item at plist.c:941:6 in plist.h
// plist_dict_copy_bool at plist.c:1171:13 in plist.h
// plist_dict_get_bool at plist.c:1032:9 in plist.h
// plist_free at plist.c:553:6 in plist.h
// plist_free at plist.c:553:6 in plist.h
// plist_free at plist.c:553:6 in plist.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare the environment
    uint8_t bool_val = Data[0];
    plist_t node = plist_new_bool(bool_val);

    // Fuzz plist_set_bool_val
    plist_set_bool_val(node, bool_val);

    // Fuzz plist_bool_val_is_true
    int is_true = plist_bool_val_is_true(node);

    // Fuzz plist_get_bool_val
    uint8_t retrieved_val = 0;
    plist_get_bool_val(node, &retrieved_val);

    // Create dictionaries for fuzzing plist_dict_copy_bool and plist_dict_get_bool
    plist_t source_dict = plist_new_dict();
    plist_t target_dict = plist_new_dict();
    const char *key = "test_key";
    const char *alt_key = "alt_test_key";

    plist_dict_set_item(source_dict, key, node);
    plist_dict_set_item(source_dict, alt_key, plist_new_bool(!bool_val));

    // Fuzz plist_dict_copy_bool
    plist_err_t copy_err = plist_dict_copy_bool(target_dict, source_dict, key, alt_key);

    // Fuzz plist_dict_get_bool
    uint8_t dict_bool_val = plist_dict_get_bool(source_dict, key);

    // Cleanup
    plist_free(node);
    plist_free(source_dict);
    plist_free(target_dict);

    return 0;
}