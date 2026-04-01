// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_dict_get_uint at plist.c:1120:10 in plist.h
// plist_write_to_stream at plist.c:1996:13 in plist.h
// plist_set_data_val at plist.c:1618:6 in plist.h
// plist_from_bin at bplist.c:847:13 in plist.h
// plist_free at plist.c:553:6 in plist.h
// plist_set_key_val at plist.c:1578:6 in plist.h
// plist_new_dict at plist.c:436:9 in plist.h
// plist_new_null at plist.c:544:9 in plist.h
// plist_free at plist.c:553:6 in plist.h
// plist_new_data at plist.c:514:9 in plist.h
// plist_free at plist.c:553:6 in plist.h
// plist_new_dict at plist.c:436:9 in plist.h
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
extern "C" {
#include <plist/plist.h>
}

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static void fuzz_plist_dict_get_uint(plist_t dict, const char* key) {
    if (key) {
        uint64_t value = plist_dict_get_uint(dict, key);
        (void)value;
    }
}

static void fuzz_plist_write_to_stream(plist_t plist) {
    FILE* stream = fopen("./dummy_file", "wb");
    if (!stream) return;

    plist_format_t format = PLIST_FORMAT_BINARY;
    plist_write_options_t options = static_cast<plist_write_options_t>(0);
    plist_err_t err = plist_write_to_stream(plist, stream, format, options);
    fclose(stream);
    (void)err;
}

static void fuzz_plist_set_data_val(plist_t node, const uint8_t* data, size_t length) {
    plist_set_data_val(node, reinterpret_cast<const char*>(data), length);
}

static void fuzz_plist_from_bin(const uint8_t* data, size_t length) {
    plist_t plist = nullptr;
    plist_err_t err = plist_from_bin(reinterpret_cast<const char*>(data), length, &plist);
    if (err == PLIST_ERR_SUCCESS && plist) {
        plist_free(plist);
    }
}

static void fuzz_plist_set_key_val(plist_t node, const char* key) {
    if (key) {
        plist_set_key_val(node, key);
    }
}

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a new plist dictionary
    plist_t dict = plist_new_dict();

    // Ensure null-terminated string for keys
    std::string key(reinterpret_cast<const char*>(Data), Size);
    key.push_back('\0');

    // Fuzz plist_dict_get_uint
    fuzz_plist_dict_get_uint(dict, key.c_str());

    // Fuzz plist_write_to_stream
    plist_t plist = plist_new_null();
    fuzz_plist_write_to_stream(plist);
    plist_free(plist);

    // Fuzz plist_set_data_val
    plist_t data_node = plist_new_data(nullptr, 0);
    fuzz_plist_set_data_val(data_node, Data, Size);
    plist_free(data_node);

    // Fuzz plist_from_bin
    fuzz_plist_from_bin(Data, Size);

    // Fuzz plist_set_key_val
    plist_t key_node = plist_new_dict(); // Use plist_new_dict as a placeholder
    fuzz_plist_set_key_val(key_node, key.c_str());
    plist_free(key_node);

    // Clean up
    plist_free(dict);

    return 0;
}