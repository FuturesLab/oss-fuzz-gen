#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "plist/plist.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

static void fuzz_plist_print(plist_t plist) {
    plist_print(plist);
}

static void fuzz_plist_get_node_type(plist_t plist) {
    plist_type type = plist_get_node_type(plist);
    (void)type; // Use type to avoid unused variable warning
}

static void fuzz_plist_write_to_stream(plist_t plist) {
    FILE* stream = fopen("./dummy_file", "w+");
    if (stream) {
        plist_err_t err = plist_write_to_stream(plist, stream, PLIST_FORMAT_PRINT, PLIST_OPT_PARTIAL_DATA);
        fclose(stream);
        (void)err; // Use err to avoid unused variable warning
    }
}

static void fuzz_plist_read_from_file() {
    plist_t plist = nullptr;
    plist_format_t format;
    plist_err_t err = plist_read_from_file("./dummy_file", &plist, &format);
    if (err == PLIST_ERR_SUCCESS && plist) {
        plist_free(plist);
    }
}

static void fuzz_plist_write_to_file(plist_t plist) {
    plist_err_t err = plist_write_to_file(plist, "./dummy_file", PLIST_FORMAT_PRINT, PLIST_OPT_PARTIAL_DATA);
    (void)err; // Use err to avoid unused variable warning
}

static void fuzz_plist_write_to_string(plist_t plist) {
    char *output = nullptr;
    uint32_t length = 0;
    plist_err_t err = plist_write_to_string(plist, &output, &length, PLIST_FORMAT_PRINT, PLIST_OPT_PARTIAL_DATA);
    if (err == PLIST_ERR_SUCCESS && output) {
        plist_mem_free(output);
    }
}

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy plist_t structure for fuzzing
    plist_t plist = nullptr;
    plist_format_t format;
    plist_err_t err = plist_from_memory(reinterpret_cast<const char*>(Data), Size, &plist, &format);

    if (err == PLIST_ERR_SUCCESS && plist) {
        fuzz_plist_print(plist);
        fuzz_plist_get_node_type(plist);
        fuzz_plist_write_to_stream(plist);
        fuzz_plist_read_from_file();
        fuzz_plist_write_to_file(plist);
        fuzz_plist_write_to_string(plist);

        plist_free(plist);
    }

    return 0;
}