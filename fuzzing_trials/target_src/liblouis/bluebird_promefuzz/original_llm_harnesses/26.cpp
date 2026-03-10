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
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

static void fuzz_lou_backTranslate(const uint8_t *Data, size_t Size) {
    if (Size == 0) return;

    const char *tableList = "./dummy_file";
    widechar *inbuf = new widechar[Size];
    int inlen = Size;
    widechar *outbuf = new widechar[Size];
    int outlen = Size;
    formtype *typeform = nullptr;
    char *spacing = nullptr;
    int *outputPos = new int[Size];
    int *inputPos = new int[Size];
    int cursorPos = 0;
    int mode = 0;

    std::memcpy(inbuf, Data, Size * sizeof(uint8_t));
    std::ofstream dummyFile(tableList);
    dummyFile << "table content";
    dummyFile.close();

    lou_backTranslate(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, mode);

    delete[] inbuf;
    delete[] outbuf;
    delete[] outputPos;
    delete[] inputPos;
}

static void fuzz_lou_translate(const uint8_t *Data, size_t Size) {
    if (Size == 0) return;

    const char *tableList = "./dummy_file";
    widechar *inbuf = new widechar[Size];
    int inlen = Size;
    widechar *outbuf = new widechar[Size];
    int outlen = Size;
    formtype *typeform = nullptr;
    char *spacing = nullptr;
    int *outputPos = new int[Size];
    int *inputPos = new int[Size];
    int cursorPos = 0;
    int mode = 0;

    std::memcpy(inbuf, Data, Size * sizeof(uint8_t));
    std::ofstream dummyFile(tableList);
    dummyFile << "table content";
    dummyFile.close();

    lou_translate(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, mode);

    delete[] inbuf;
    delete[] outbuf;
    delete[] outputPos;
    delete[] inputPos;
}

static void fuzz_lou_translateString(const uint8_t *Data, size_t Size) {
    if (Size == 0) return;

    const char *tableList = "./dummy_file";
    widechar *inbuf = new widechar[Size];
    int inlen = Size;
    widechar *outbuf = new widechar[Size];
    int outlen = Size;
    formtype *typeform = nullptr;
    char *spacing = nullptr;
    int mode = 0;

    std::memcpy(inbuf, Data, Size * sizeof(uint8_t));
    std::ofstream dummyFile(tableList);
    dummyFile << "table content";
    dummyFile.close();

    lou_translateString(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, mode);

    delete[] inbuf;
    delete[] outbuf;
}

static void fuzz_lou_translatePrehyphenated(const uint8_t *Data, size_t Size) {
    if (Size == 0) return;

    const char *tableList = "./dummy_file";
    widechar *inbuf = new widechar[Size];
    int inlen = Size;
    widechar *outbuf = new widechar[Size];
    int outlen = Size;
    formtype *typeform = nullptr;
    char *spacing = nullptr;
    int *outputPos = new int[Size];
    int *inputPos = new int[Size];
    int cursorPos = 0;
    char *inputHyphens = new char[Size];
    char *outputHyphens = new char[Size];
    int mode = 0;

    std::memcpy(inbuf, Data, Size * sizeof(uint8_t));
    std::ofstream dummyFile(tableList);
    dummyFile << "table content";
    dummyFile.close();

    lou_translatePrehyphenated(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, inputHyphens, outputHyphens, mode);

    delete[] inbuf;
    delete[] outbuf;
    delete[] outputPos;
    delete[] inputPos;
    delete[] inputHyphens;
    delete[] outputHyphens;
}

static void fuzz_lou_hyphenate(const uint8_t *Data, size_t Size) {
    if (Size == 0) return;

    const char *tableList = "./dummy_file";
    widechar *inbuf = new widechar[Size];
    int inlen = Size;
    char *hyphens = new char[Size];
    int mode = 0;

    std::memcpy(inbuf, Data, Size * sizeof(uint8_t));
    std::ofstream dummyFile(tableList);
    dummyFile << "table content";
    dummyFile.close();

    lou_hyphenate(tableList, inbuf, inlen, hyphens, mode);

    delete[] inbuf;
    delete[] hyphens;
}

static void fuzz_lou_checkTable(const uint8_t *Data, size_t Size) {
    const char *tableList = "./dummy_file";
    std::ofstream dummyFile(tableList);
    dummyFile << "table content";
    dummyFile.close();

    lou_checkTable(tableList);
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    fuzz_lou_backTranslate(Data, Size);
    fuzz_lou_translate(Data, Size);
    fuzz_lou_translateString(Data, Size);
    fuzz_lou_translatePrehyphenated(Data, Size);
    fuzz_lou_hyphenate(Data, Size);
    fuzz_lou_checkTable(Data, Size);
    return 0;
}