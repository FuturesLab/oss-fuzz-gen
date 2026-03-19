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
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Prepare a dummy plist_t object
    plist_t plist = nullptr;
    plist_from_xml(reinterpret_cast<const char*>(Data), static_cast<uint32_t>(Size), &plist);

    // Variables to hold output data
    char *output = nullptr;
    uint32_t length = 0;
    plist_err_t result;

    // Fuzz plist_to_xml
    result = plist_to_xml(plist, &output, &length);
    if (result == PLIST_ERR_SUCCESS && output != nullptr) {
        plist_mem_free(output);
    }

    // Fuzz plist_to_json
    result = plist_to_json(plist, &output, &length, 1); // with prettify
    if (result == PLIST_ERR_SUCCESS && output != nullptr) {
        plist_mem_free(output);
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_to_json to plist_get_data_ptr
    plist_t ret_plist_get_parent_uysai = plist_get_parent(plist);

    const char* ret_plist_get_data_ptr_olspc = plist_get_data_ptr(ret_plist_get_parent_uysai, (uint64_t *)&length);
    if (ret_plist_get_data_ptr_olspc == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    result = plist_to_json(plist, &output, &length, 0); // without prettify
    if (result == PLIST_ERR_SUCCESS && output != nullptr) {
        plist_mem_free(output);
    }

    // Fuzz plist_to_bin
    result = plist_to_bin(plist, &output, &length);
    if (result == PLIST_ERR_SUCCESS && output != nullptr) {
        plist_mem_free(output);
    }

    // Fuzz plist_to_openstep
    result = plist_to_openstep(plist, &output, &length, 1); // with prettify
    if (result == PLIST_ERR_SUCCESS && output != nullptr) {
        plist_mem_free(output);
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_to_openstep to plist_to_json
    plist_t ret_plist_new_uid_pzbtk = plist_new_uid(-1);
    uint32_t ret_plist_array_get_size_ljajb = plist_array_get_size(0);
    if (ret_plist_array_get_size_ljajb < 0){
    	return 0;
    }

    plist_err_t ret_plist_to_json_wukyu = plist_to_json(ret_plist_new_uid_pzbtk, (char **)"w", &length, (int )ret_plist_array_get_size_ljajb);

    // End mutation: Producer.APPEND_MUTATOR

    result = plist_to_openstep(plist, &output, &length, 0); // without prettify
    if (result == PLIST_ERR_SUCCESS && output != nullptr) {
        plist_mem_free(output);
    }

    // Fuzz plist_write_to_string
    result = plist_write_to_string(plist, &output, &length, PLIST_FORMAT_XML, static_cast<plist_write_options_t>(0));
    if (result == PLIST_ERR_SUCCESS && output != nullptr) {
        plist_mem_free(output);
    }

    result = plist_write_to_string(plist, &output, &length, PLIST_FORMAT_JSON, static_cast<plist_write_options_t>(0));
    if (result == PLIST_ERR_SUCCESS && output != nullptr) {
        plist_mem_free(output);
    }

    // Clean up plist object
    if (plist != nullptr) {
        plist_free(plist);
    }    return 0;
}