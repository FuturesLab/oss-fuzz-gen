// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_translatePrehyphenated at lou_translateString.c:1410:1 in liblouis.h
// lou_hyphenate at lou_translateString.c:4066:1 in liblouis.h
// lou_checkTable at compileTranslationTable.c:5238:1 in liblouis.h
// lou_backTranslate at lou_backTranslateString.c:159:1 in liblouis.h
// lou_translate at lou_translateString.c:1135:1 in liblouis.h
// lou_translateString at lou_translateString.c:1128:1 in liblouis.h
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

static void fuzz_lou_backTranslate(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 5 + 1) return;

    const char *tableList = reinterpret_cast<const char *>(Data);
    size_t tableListLen = strnlen(tableList, Size);
    if (tableListLen == Size) return; // Ensure null-termination

    widechar *inbuf = new widechar[Size];
    std::memcpy(inbuf, Data, Size);

    int inlen = Size / sizeof(widechar);
    int outlen = inlen * 2;
    widechar *outbuf = new widechar[outlen];
    formtype *typeform = nullptr;
    char *spacing = nullptr;
    int *outputPos = new int[inlen];
    int *inputPos = new int[outlen];
    int cursorPos = 0;
    int mode = *reinterpret_cast<const int *>(Data + Size - sizeof(int));

    lou_backTranslate(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, mode);

    delete[] inbuf;
    delete[] outbuf;
    delete[] outputPos;
    delete[] inputPos;
}

static void fuzz_lou_translate(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 5 + 1) return;

    const char *tableList = reinterpret_cast<const char *>(Data);
    size_t tableListLen = strnlen(tableList, Size);
    if (tableListLen == Size) return; // Ensure null-termination

    widechar *inbuf = new widechar[Size];
    std::memcpy(inbuf, Data, Size);

    int inlen = Size / sizeof(widechar);
    int outlen = inlen * 2;
    widechar *outbuf = new widechar[outlen];
    formtype *typeform = nullptr;
    char *spacing = nullptr;
    int *outputPos = new int[inlen];
    int *inputPos = new int[outlen];
    int cursorPos = 0;
    int mode = *reinterpret_cast<const int *>(Data + Size - sizeof(int));

    lou_translate(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, mode);

    delete[] inbuf;
    delete[] outbuf;
    delete[] outputPos;
    delete[] inputPos;
}

static void fuzz_lou_translateString(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 3 + 1) return;

    const char *tableList = reinterpret_cast<const char *>(Data);
    size_t tableListLen = strnlen(tableList, Size);
    if (tableListLen == Size) return; // Ensure null-termination

    widechar *inbuf = new widechar[Size];
    std::memcpy(inbuf, Data, Size);

    int inlen = Size / sizeof(widechar);
    int outlen = inlen * 2;
    widechar *outbuf = new widechar[outlen];
    formtype *typeform = nullptr;
    char *spacing = nullptr;
    int mode = *reinterpret_cast<const int *>(Data + Size - sizeof(int));

    lou_translateString(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, mode);

    delete[] inbuf;
    delete[] outbuf;
}

static void fuzz_lou_translatePrehyphenated(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 5 + 1) return;

    const char *tableList = reinterpret_cast<const char *>(Data);
    size_t tableListLen = strnlen(tableList, Size);
    if (tableListLen == Size) return; // Ensure null-termination

    widechar *inbuf = new widechar[Size];
    std::memcpy(inbuf, Data, Size);

    int inlen = Size / sizeof(widechar);
    int outlen = inlen * 2;
    widechar *outbuf = new widechar[outlen];
    formtype *typeform = nullptr;
    char *spacing = nullptr;
    int *outputPos = new int[inlen];
    int *inputPos = new int[outlen];
    int cursorPos = 0;
    char *inputHyphens = new char[inlen];
    char *outputHyphens = new char[outlen];
    int mode = *reinterpret_cast<const int *>(Data + Size - sizeof(int));

    lou_translatePrehyphenated(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, inputHyphens, outputHyphens, mode);

    delete[] inbuf;
    delete[] outbuf;
    delete[] outputPos;
    delete[] inputPos;
    delete[] inputHyphens;
    delete[] outputHyphens;
}

static void fuzz_lou_hyphenate(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) + 1) return;

    const char *tableList = reinterpret_cast<const char *>(Data);
    size_t tableListLen = strnlen(tableList, Size);
    if (tableListLen == Size) return; // Ensure null-termination

    widechar *inbuf = new widechar[Size];
    std::memcpy(inbuf, Data, Size);

    int inlen = Size / sizeof(widechar);
    char *hyphens = new char[inlen];
    int mode = *reinterpret_cast<const int *>(Data + Size - sizeof(int));

    lou_hyphenate(tableList, inbuf, inlen, hyphens, mode);

    delete[] inbuf;
    delete[] hyphens;
}

static void fuzz_lou_checkTable(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    // Ensure null-termination for tableList
    char *tableList = new char[Size + 1];
    std::memcpy(tableList, Data, Size);
    tableList[Size] = '\0';

    lou_checkTable(tableList);

    delete[] tableList;
}

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    fuzz_lou_backTranslate(Data, Size);
    fuzz_lou_translate(Data, Size);
    fuzz_lou_translateString(Data, Size);
    fuzz_lou_translatePrehyphenated(Data, Size);
    fuzz_lou_hyphenate(Data, Size);
    fuzz_lou_checkTable(Data, Size);
    return 0;
}