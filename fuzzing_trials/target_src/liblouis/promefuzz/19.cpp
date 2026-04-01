// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_backTranslate at lou_backTranslateString.c:159:1 in liblouis.h
// lou_translate at lou_translateString.c:1135:1 in liblouis.h
// lou_translateString at lou_translateString.c:1128:1 in liblouis.h
// lou_backTranslateString at lou_backTranslateString.c:152:1 in liblouis.h
// lou_checkTable at compileTranslationTable.c:5238:1 in liblouis.h
// lou_dotsToChar at lou_translateString.c:4150:1 in liblouis.h
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
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Prepare dummy file for tableList
    std::ofstream dummyFile("./dummy_file");
    if (!dummyFile.is_open()) return 0;
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    const char* tableList = "./dummy_file";
    int mode = 0;

    // Prepare buffers and lengths
    widechar inbuf[256];
    widechar outbuf[256];
    formtype typeform[256];
    char spacing[256];
    int outputPos[256];
    int inputPos[256];
    int cursorPos = 0;
    int inlen = Size < 256 ? Size : 256;
    int outlen = 256;

    std::memset(inbuf, 0, sizeof(inbuf));
    std::memset(outbuf, 0, sizeof(outbuf));
    std::memset(typeform, 0, sizeof(typeform));
    std::memset(spacing, 0, sizeof(spacing));
    std::memset(outputPos, 0, sizeof(outputPos));
    std::memset(inputPos, 0, sizeof(inputPos));

    // Copy input data to inbuf
    for (int i = 0; i < inlen; ++i) {
        inbuf[i] = Data[i];
    }

    // Fuzzing lou_backTranslate
    lou_backTranslate(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, mode);

    // Reset lengths and buffers for next function
    inlen = Size < 256 ? Size : 256;
    outlen = 256;
    std::memset(outbuf, 0, sizeof(outbuf));

    // Fuzzing lou_translate
    lou_translate(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, mode);

    // Reset lengths and buffers for next function
    inlen = Size < 256 ? Size : 256;
    outlen = 256;
    std::memset(outbuf, 0, sizeof(outbuf));

    // Fuzzing lou_translateString
    lou_translateString(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, mode);

    // Reset lengths and buffers for next function
    inlen = Size < 256 ? Size : 256;
    outlen = 256;
    std::memset(outbuf, 0, sizeof(outbuf));

    // Fuzzing lou_backTranslateString
    lou_backTranslateString(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, mode);

    // Fuzzing lou_checkTable
    lou_checkTable(tableList);

    // Reset buffers for next function
    std::memset(inbuf, 0, sizeof(inbuf));
    std::memset(outbuf, 0, sizeof(outbuf));

    // Fuzzing lou_dotsToChar
    lou_dotsToChar(tableList, inbuf, outbuf, inlen, mode);

    return 0;
}