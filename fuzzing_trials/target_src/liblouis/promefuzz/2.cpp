// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_registerLogCallback at logging.c:86:1 in liblouis.h
// lou_checkTable at compileTranslationTable.c:5238:1 in liblouis.h
// lou_free at compileTranslationTable.c:5363:1 in liblouis.h
// lou_backTranslateString at lou_backTranslateString.c:152:1 in liblouis.h
// lou_free at compileTranslationTable.c:5363:1 in liblouis.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <liblouis.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    // Prepare environment
    if (Size < 1) return 0;

    // Register a log callback
    lou_registerLogCallback(nullptr);

    // Prepare a dummy table file
    std::ofstream dummyFile("./dummy_file");
    if (dummyFile.is_open()) {
        dummyFile.write(reinterpret_cast<const char*>(Data), Size);
        dummyFile.close();
    }

    // Check table
    lou_checkTable("./dummy_file");

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