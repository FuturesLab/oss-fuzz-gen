// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_hyphenate at lou_translateString.c:4066:1 in liblouis.h
// lou_checkTable at compileTranslationTable.c:5238:1 in liblouis.h
// lou_backTranslate at lou_backTranslateString.c:159:1 in liblouis.h
// lou_translate at lou_translateString.c:1135:1 in liblouis.h
// lou_translateString at lou_translateString.c:1128:1 in liblouis.h
// lou_translatePrehyphenated at lou_translateString.c:1410:1 in liblouis.h
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
#include <cstring>
#include <cstdlib>
#include <fstream>

static void fuzz_lou_backTranslate(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(widechar) + 1) return; // Ensure there's at least one widechar and null terminator
    const char *tableList = reinterpret_cast<const char *>(Data);
    if (tableList[Size - 1] != '\0') return; // Ensure null-terminated string
    const widechar *inbuf = reinterpret_cast<const widechar *>(Data);
    int inlen = Size / sizeof(widechar);
    widechar *outbuf = new widechar[inlen];
    int outlen = inlen;
    int *outputPos = new int[inlen];
    int *inputPos = new int[outlen];
    int cursorPos = 0;
    int mode = 0;

    lou_backTranslate(tableList, inbuf, &inlen, outbuf, &outlen, nullptr, nullptr, outputPos, inputPos, &cursorPos, mode);

    delete[] outbuf;
    delete[] outputPos;
    delete[] inputPos;
}

static void fuzz_lou_translate(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(widechar) + 1) return; // Ensure there's at least one widechar and null terminator
    const char *tableList = reinterpret_cast<const char *>(Data);
    if (tableList[Size - 1] != '\0') return; // Ensure null-terminated string
    const widechar *inbuf = reinterpret_cast<const widechar *>(Data);
    int inlen = Size / sizeof(widechar);
    widechar *outbuf = new widechar[inlen];
    int outlen = inlen;
    int *outputPos = new int[inlen];
    int *inputPos = new int[outlen];
    int cursorPos = 0;
    int mode = 0;

    lou_translate(tableList, inbuf, &inlen, outbuf, &outlen, nullptr, nullptr, outputPos, inputPos, &cursorPos, mode);

    delete[] outbuf;
    delete[] outputPos;
    delete[] inputPos;
}

static void fuzz_lou_translateString(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(widechar) + 1) return; // Ensure there's at least one widechar and null terminator
    const char *tableList = reinterpret_cast<const char *>(Data);
    if (tableList[Size - 1] != '\0') return; // Ensure null-terminated string
    const widechar *inbuf = reinterpret_cast<const widechar *>(Data);
    int inlen = Size / sizeof(widechar);
    widechar *outbuf = new widechar[inlen];
    int outlen = inlen;
    int mode = 0;

    lou_translateString(tableList, inbuf, &inlen, outbuf, &outlen, nullptr, nullptr, mode);

    delete[] outbuf;
}

static void fuzz_lou_translatePrehyphenated(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(widechar) + 1) return; // Ensure there's at least one widechar and null terminator
    const char *tableList = reinterpret_cast<const char *>(Data);
    if (tableList[Size - 1] != '\0') return; // Ensure null-terminated string
    const widechar *inbuf = reinterpret_cast<const widechar *>(Data);
    int inlen = Size / sizeof(widechar);
    widechar *outbuf = new widechar[inlen];
    int outlen = inlen;
    int *outputPos = new int[inlen];
    int *inputPos = new int[outlen];
    int cursorPos = 0;
    char *inputHyphens = new char[inlen];
    char *outputHyphens = new char[outlen];
    int mode = 0;

    lou_translatePrehyphenated(tableList, inbuf, &inlen, outbuf, &outlen, nullptr, nullptr, outputPos, inputPos, &cursorPos, inputHyphens, outputHyphens, mode);

    delete[] outbuf;
    delete[] outputPos;
    delete[] inputPos;
    delete[] inputHyphens;
    delete[] outputHyphens;
}

static void fuzz_lou_hyphenate(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(widechar) + 1) return; // Ensure there's at least one widechar and null terminator
    const char *tableList = reinterpret_cast<const char *>(Data);
    if (tableList[Size - 1] != '\0') return; // Ensure null-terminated string
    const widechar *inbuf = reinterpret_cast<const widechar *>(Data);
    int inlen = Size / sizeof(widechar);
    char *hyphens = new char[inlen];
    int mode = 0;

    lou_hyphenate(tableList, inbuf, inlen, hyphens, mode);

    delete[] hyphens;
}

static void fuzz_lou_checkTable(const uint8_t *Data, size_t Size) {
    if (Size == 0 || Data[Size - 1] != '\0') return; // Ensure null-terminated string
    const char *tableList = reinterpret_cast<const char *>(Data);
    lou_checkTable(tableList);
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    fuzz_lou_backTranslate(Data, Size);
    fuzz_lou_translate(Data, Size);
    fuzz_lou_translateString(Data, Size);
    fuzz_lou_translatePrehyphenated(Data, Size);
    fuzz_lou_hyphenate(Data, Size);
    fuzz_lou_checkTable(Data, Size);
    return 0;
}