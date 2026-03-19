// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_from_xml at xplist.c:1599:13 in plist.h
// plist_to_xml at xplist.c:574:13 in plist.h
// plist_mem_free at plist.c:561:6 in plist.h
// plist_to_json at jplist.c:429:13 in plist.h
// plist_mem_free at plist.c:561:6 in plist.h
// plist_to_bin at bplist.c:1302:13 in plist.h
// plist_mem_free at plist.c:561:6 in plist.h
// plist_to_openstep at oplist.c:473:13 in plist.h
// plist_mem_free at plist.c:561:6 in plist.h
// plist_write_to_string at plist.c:1966:13 in plist.h
// plist_mem_free at plist.c:561:6 in plist.h
// plist_write_to_string at plist.c:1966:13 in plist.h
// plist_mem_free at plist.c:561:6 in plist.h
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
#include "plist.h"

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Convert input data to a null-terminated string
    char *inputData = static_cast<char *>(malloc(Size + 1));
    if (!inputData) return 0;
    memcpy(inputData, Data, Size);
    inputData[Size] = '\0';

    plist_t plist = nullptr;
    plist_err_t err;

    // Attempt to parse input data as XML plist
    err = plist_from_xml(inputData, static_cast<uint32_t>(Size), &plist);
    if (err == PLIST_ERR_SUCCESS && plist != nullptr) {
        char *output = nullptr;
        uint32_t length = 0;

        // Test plist_to_xml
        err = plist_to_xml(plist, &output, &length);
        if (err == PLIST_ERR_SUCCESS) {
            plist_mem_free(output);
        }

        // Test plist_to_json
        err = plist_to_json(plist, &output, &length, 1);
        if (err == PLIST_ERR_SUCCESS) {
            plist_mem_free(output);
        }

        // Test plist_to_bin
        err = plist_to_bin(plist, &output, &length);
        if (err == PLIST_ERR_SUCCESS) {
            plist_mem_free(output);
        }

        // Test plist_to_openstep
        err = plist_to_openstep(plist, &output, &length, 1);
        if (err == PLIST_ERR_SUCCESS) {
            plist_mem_free(output);
        }

        // Test plist_write_to_string with different formats and options
        err = plist_write_to_string(plist, &output, &length, PLIST_FORMAT_XML, static_cast<plist_write_options_t>(0));
        if (err == PLIST_ERR_SUCCESS) {
            plist_mem_free(output);
        }

        err = plist_write_to_string(plist, &output, &length, PLIST_FORMAT_JSON, static_cast<plist_write_options_t>(0));
        if (err == PLIST_ERR_SUCCESS) {
            plist_mem_free(output);
        }

        // Free the plist structure
        plist_free(plist);
    }

    free(inputData);
    return 0;
}