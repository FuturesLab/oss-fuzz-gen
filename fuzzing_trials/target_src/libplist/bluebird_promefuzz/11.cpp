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
#include "plist/plist.h"
}

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>

static void fuzz_plist_set_debug(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int debug_level = *reinterpret_cast<const int*>(Data);
    plist_set_debug(debug_level);
}

static void fuzz_plist_to_json(const uint8_t *Data, size_t Size) {
    plist_t plist = nullptr;
    char *json_output = nullptr;
    uint32_t length = 0;

    plist_from_memory(reinterpret_cast<const char*>(Data), Size, &plist, nullptr);
    if (plist) {
        plist_to_json(plist, &json_output, &length, 0);
        if (json_output) {
            plist_mem_free(json_output);
        }
        plist_free(plist);
    }
}

static void fuzz_plist_from_json(const uint8_t *Data, size_t Size) {
    plist_t plist = nullptr;
    plist_from_json(reinterpret_cast<const char*>(Data), Size, &plist);
    if (plist) {
        plist_free(plist);
    }
}

static void fuzz_plist_from_memory(const uint8_t *Data, size_t Size) {
    plist_t plist = nullptr;
    plist_from_memory(reinterpret_cast<const char*>(Data), Size, &plist, nullptr);
    if (plist) {
        plist_free(plist);
    }
}

static void fuzz_plist_from_xml(const uint8_t *Data, size_t Size) {
    plist_t plist = nullptr;
    plist_from_xml(reinterpret_cast<const char*>(Data), Size, &plist);
    if (plist) {
        plist_free(plist);
    }
}

static void fuzz_plist_read_from_file(const uint8_t *Data, size_t Size) {
    std::ofstream file("./dummy_file", std::ios::binary);
    if (!file) return;
    file.write(reinterpret_cast<const char*>(Data), Size);
    file.close();

    plist_t plist = nullptr;
    plist_read_from_file("./dummy_file", &plist, nullptr);
    if (plist) {
        plist_free(plist);
    }
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    fuzz_plist_set_debug(Data, Size);
    fuzz_plist_to_json(Data, Size);
    fuzz_plist_from_json(Data, Size);
    fuzz_plist_from_memory(Data, Size);
    fuzz_plist_from_xml(Data, Size);
    fuzz_plist_read_from_file(Data, Size);
    return 0;
}