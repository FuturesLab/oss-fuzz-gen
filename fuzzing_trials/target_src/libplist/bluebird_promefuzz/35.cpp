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
#include <iostream>
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    plist_t plist = nullptr;
    plist_format_t format;
    char *plist_bin = nullptr;
    uint32_t bin_length = 0;
    char *plist_str = nullptr;
    uint32_t str_length = 0;

    // Fuzz plist_from_memory
    plist_err_t err = plist_from_memory(reinterpret_cast<const char*>(Data), static_cast<uint32_t>(Size), &plist, &format);
    if (err == PLIST_ERR_SUCCESS && plist != nullptr) {
        // Fuzz plist_print
        plist_print(plist);

        // Fuzz plist_to_bin
        err = plist_to_bin(plist, &plist_bin, &bin_length);
        if (err == PLIST_ERR_SUCCESS && plist_bin != nullptr) {
            free(plist_bin);
        }

        // Fuzz plist_write_to_string

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_to_bin to plist_key_val_contains
        plist_t ret_plist_new_int_qjrka = plist_new_int(0);

        int ret_plist_key_val_contains_vovcg = plist_key_val_contains(ret_plist_new_int_qjrka, plist_bin);
        if (ret_plist_key_val_contains_vovcg < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        err = plist_write_to_string(plist, &plist_str, &str_length, format, PLIST_OPT_NONE);
        if (err == PLIST_ERR_SUCCESS && plist_str != nullptr) {
            free(plist_str);
        }

        // Fuzz plist_write_to_file
        plist_write_to_file(plist, "./dummy_file", format, PLIST_OPT_NONE);

        plist_free(plist);
    }

    // Fuzz plist_read_from_file
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    plist_t plist_from_file = nullptr;
    err = plist_read_from_file("./dummy_file", &plist_from_file, &format);
    if (err == PLIST_ERR_SUCCESS && plist_from_file != nullptr) {
        plist_free(plist_from_file);
    }
    return 0;
}