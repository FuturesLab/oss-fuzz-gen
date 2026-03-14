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

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
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
    lou_checkTable((const char *)"r");
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Free resources

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function lou_free with lou_logEnd

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function lou_logEnd with lou_free
    lou_free();
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Prepare input for backTranslateString
    widechar inbuf[1024];
    int inlen = std::min(Size / sizeof(widechar), sizeof(inbuf) / sizeof(widechar));
    std::memcpy(inbuf, Data, inlen * sizeof(widechar));

    widechar outbuf[1024];
    int outlen = sizeof(outbuf) / sizeof(widechar);

    // Back translate string

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function lou_backTranslateString with lou_translateString
    lou_translateString("./dummy_file", inbuf, &inlen, outbuf, &outlen, NULL, NULL, 0);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Free resources again

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function lou_free with lou_logEnd
    lou_logEnd();
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}