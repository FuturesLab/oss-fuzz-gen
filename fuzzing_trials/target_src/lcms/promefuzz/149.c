// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsMLUalloc at cmsnamed.c:33:19 in lcms2.h
// cmsMLUdup at cmsnamed.c:430:19 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
// cmsMLUsetUTF8 at cmsnamed.c:368:19 in lcms2.h
// cmsMLUgetTranslation at cmsnamed.c:663:26 in lcms2.h
// cmsMLUsetWide at cmsnamed.c:413:20 in lcms2.h
// cmsDictAlloc at cmsnamed.c:1090:21 in lcms2.h
// cmsDictAddEntry at cmsnamed.c:1137:19 in lcms2.h
// cmsDictFree at cmsnamed.c:1101:16 in lcms2.h
// cmsMLUsetASCII at cmsnamed.c:336:19 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_149(const uint8_t *Data, size_t Size) {
    if (Size < 3) return 0;

    cmsMLU* mlu = cmsMLUalloc(NULL, 0);
    if (!mlu) return 0;

    // Fuzz cmsMLUdup
    cmsMLU* dupMlu = cmsMLUdup(mlu);
    if (dupMlu) {
        cmsMLUfree(dupMlu);
    }

    // Fuzz cmsMLUsetUTF8
    if (Size >= 7) { // Ensure enough data for language, country, and at least 1 char UTF8 string
        size_t utf8Length = Size - 6;
        char* utf8String = (char*)malloc(utf8Length + 1);
        if (utf8String) {
            memcpy(utf8String, &Data[6], utf8Length);
            utf8String[utf8Length] = '\0'; // Null-terminate to prevent overflow
            cmsMLUsetUTF8(mlu, (const char*)&Data[0], (const char*)&Data[3], utf8String);
            free(utf8String);
        }
    }

    // Fuzz cmsMLUgetTranslation
    char obtainedLang[3] = {0};
    char obtainedCountry[3] = {0};
    if (Size >= 6) {
        cmsMLUgetTranslation(mlu, (const char*)&Data[0], (const char*)&Data[3], obtainedLang, obtainedCountry);
    }

    // Fuzz cmsMLUsetWide
    wchar_t wideString[5] = L"Test";
    cmsMLUsetWide(mlu, "en", "US", wideString);

    // Fuzz cmsDictAddEntry
    cmsHANDLE hDict = cmsDictAlloc(NULL);
    if (hDict) {
        cmsDictAddEntry(hDict, L"Name", L"Value", mlu, mlu);
        cmsDictFree(hDict);
    }

    // Fuzz cmsMLUsetASCII
    const char* asciiString = "ASCII";
    cmsMLUsetASCII(mlu, "en", "US", asciiString);

    cmsMLUfree(mlu);
    return 0;
}