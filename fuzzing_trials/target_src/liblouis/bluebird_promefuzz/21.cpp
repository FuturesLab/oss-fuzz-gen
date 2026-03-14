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

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
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
    lou_logEnd();
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lou_translateString to lou_charToDots
    const char oqvkdfxp[1024] = "urbym";

    int ret_lou_charToDots_devci = lou_charToDots(oqvkdfxp, outbuf, NULL, 0, inlen);
    if (ret_lou_charToDots_devci < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lou_charToDots to lou_dotsToChar
    char* ret_lou_setDataPath_bkbzk = lou_setDataPath((const char *)"w");
    if (ret_lou_setDataPath_bkbzk == NULL){
    	return 0;
    }
    const char ccpfchrf[1024] = "xirum";
    int ret_lou_checkTable_ocnbc = lou_checkTable(ccpfchrf);
    if (ret_lou_checkTable_ocnbc < 0){
    	return 0;
    }
    widechar evfnwhhd;
    memset(&evfnwhhd, 0, sizeof(evfnwhhd));

    int ret_lou_dotsToChar_dixjy = lou_dotsToChar(ret_lou_setDataPath_bkbzk, NULL, &evfnwhhd, ret_lou_checkTable_ocnbc, ret_lou_charToDots_devci);
    if (ret_lou_dotsToChar_dixjy < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    lou_free();

    return 0;
}