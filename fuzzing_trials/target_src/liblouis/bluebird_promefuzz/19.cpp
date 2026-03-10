#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "../../liblouis/liblouis.h"
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    // Prepare environment
    if (Size < 1) {
        return 0;
    }

    // Register a log callback
    lou_registerLogCallback(nullptr);

    // Prepare a dummy table file
    std::ofstream dummyFile("./dummy_file");
    if (dummyFile.is_open()) {
        dummyFile.write(reinterpret_cast<const char*>(Data), Size);
        dummyFile.close();
    }

    // Check table

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of lou_checkTable

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of lou_checkTable
    const char pyjyezds[1024] = "ovfgd";
    lou_checkTable(pyjyezds);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Free resources
    lou_free();

    // Prepare input for backTranslateString
    widechar inbuf[1024];
    int inlen = std::min(Size / sizeof(widechar), sizeof(inbuf) / sizeof(widechar));
    std::memcpy(inbuf, Data, inlen * sizeof(widechar));

    widechar outbuf[1024];
    int outlen = sizeof(outbuf) / sizeof(widechar);

    // Back translate string
    lou_backTranslateString("./dummy_file", inbuf, &inlen, outbuf, &outlen, nullptr, nullptr, 0);

    // Free resources again
    lou_free();

    return 0;
}