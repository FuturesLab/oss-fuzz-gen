// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_translateString at lou_translateString.c:1128:1 in liblouis.h
// lou_compileString at compileTranslationTable.c:5430:1 in liblouis.h
// lou_hyphenate at lou_translateString.c:4066:1 in liblouis.h
// lou_checkTable at compileTranslationTable.c:5238:1 in liblouis.h
// lou_charSize at compileTranslationTable.c:5425:1 in liblouis.h
// lou_readCharFromFile at compileTranslationTable.c:4352:1 in liblouis.h
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

static void fuzz_lou_translateString(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;

    const char *tableList = reinterpret_cast<const char*>(Data);
    size_t tableListLen = strnlen(tableList, Size);
    if (tableListLen >= Size - 1) return;

    const widechar *inbuf = reinterpret_cast<const widechar*>(Data + tableListLen + 1);
    int inlen = (Size - tableListLen - 1) / sizeof(widechar);
    if (inlen <= 0) return;

    widechar outbuf[256];
    int outlen = 256;
    formtype *typeform = nullptr;
    char *spacing = nullptr;
    int mode = 0;

    lou_translateString(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, mode);
}

static void fuzz_lou_compileString(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;

    const char *tableList = reinterpret_cast<const char*>(Data);
    size_t tableListLen = strnlen(tableList, Size);
    if (tableListLen >= Size - 1) return;

    const char *inString = reinterpret_cast<const char*>(Data + tableListLen + 1);
    size_t inStringLen = strnlen(inString, Size - tableListLen - 1);

    // Ensure inString is null-terminated within its allocated bounds
    std::vector<char> nullTerminatedInString(inString, inString + inStringLen);
    nullTerminatedInString.push_back('\0');

    lou_compileString(tableList, nullTerminatedInString.data());
}

static void fuzz_lou_hyphenate(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;

    const char *tableList = reinterpret_cast<const char*>(Data);
    size_t tableListLen = strnlen(tableList, Size);
    if (tableListLen >= Size - 1) return;

    const widechar *inbuf = reinterpret_cast<const widechar*>(Data + tableListLen + 1);
    int inlen = (Size - tableListLen - 1) / sizeof(widechar);
    if (inlen <= 0) return;

    char hyphens[256];
    int mode = 0;

    lou_hyphenate(tableList, inbuf, inlen, hyphens, mode);
}

static void fuzz_lou_checkTable(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    const char *tableList = reinterpret_cast<const char*>(Data);
    if (strnlen(tableList, Size) >= Size) return;

    lou_checkTable(tableList);
}

static void fuzz_lou_charSize() {
    lou_charSize();
}

static void fuzz_lou_readCharFromFile(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    std::ofstream dummyFile("./dummy_file");
    if (!dummyFile) return;

    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    int mode = 0;
    lou_readCharFromFile("./dummy_file", &mode);
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    fuzz_lou_translateString(Data, Size);
    fuzz_lou_compileString(Data, Size);
    fuzz_lou_hyphenate(Data, Size);
    fuzz_lou_checkTable(Data, Size);
    fuzz_lou_charSize();
    fuzz_lou_readCharFromFile(Data, Size);

    return 0;
}