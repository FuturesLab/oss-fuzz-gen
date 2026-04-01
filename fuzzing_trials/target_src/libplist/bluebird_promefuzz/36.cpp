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
#include <fstream>
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Prepare a dummy file if needed
    std::ofstream dummyFile("./dummy_file", std::ios::binary);
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    // Test plist_from_xml
    plist_t plist_xml = nullptr;
    plist_err_t xml_err = plist_from_xml(reinterpret_cast<const char*>(Data), static_cast<uint32_t>(Size), &plist_xml);
    if (xml_err == PLIST_ERR_SUCCESS && plist_xml) {
        // Test plist_to_bin
        char *bin_data = nullptr;
        uint32_t bin_length = 0;
        plist_err_t bin_err = plist_to_bin(plist_xml, &bin_data, &bin_length);
        if (bin_err == PLIST_ERR_SUCCESS) {
            // Test plist_from_bin
            plist_t plist_bin = nullptr;
            plist_err_t bin_import_err = plist_from_bin(bin_data, bin_length, &plist_bin);
            if (bin_import_err == PLIST_ERR_SUCCESS && plist_bin) {
                // Test plist_dict_remove_item with a dummy key
                plist_dict_remove_item(plist_bin, "dummy_key");
                plist_free(plist_bin);
            }
            plist_mem_free(bin_data);
        }

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_to_bin to plist_from_bin
        int ret_plist_bool_val_is_true_ullyk = plist_bool_val_is_true(plist_xml);
        if (ret_plist_bool_val_is_true_ullyk < 0){
        	return 0;
        }
        plist_t ret_plist_dict_item_get_key_mxbem = plist_dict_item_get_key(0);

        plist_err_t ret_plist_from_bin_iuudn = plist_from_bin(bin_data, (uint32_t )ret_plist_bool_val_is_true_ullyk, &ret_plist_dict_item_get_key_mxbem);

        // End mutation: Producer.APPEND_MUTATOR

        plist_free(plist_xml);
    }

    // Test plist_is_binary
    int is_binary = plist_is_binary(reinterpret_cast<const char*>(Data), static_cast<uint32_t>(Size));

    return 0;
}