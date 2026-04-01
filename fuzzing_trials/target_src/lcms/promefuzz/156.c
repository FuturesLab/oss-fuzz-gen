// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsMLUalloc at cmsnamed.c:33:19 in lcms2.h
// cmsMLUdup at cmsnamed.c:430:19 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
// cmsMLUsetUTF8 at cmsnamed.c:368:19 in lcms2.h
// cmsMLUgetTranslation at cmsnamed.c:663:26 in lcms2.h
// cmsMLUsetWide at cmsnamed.c:413:20 in lcms2.h
// cmsMLUsetASCII at cmsnamed.c:336:19 in lcms2.h
// cmsDictAlloc at cmsnamed.c:1090:21 in lcms2.h
// cmsDictAddEntry at cmsnamed.c:1137:19 in lcms2.h
// cmsDictFree at cmsnamed.c:1101:16 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_156(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure there are enough bytes for LanguageCode and CountryCode

    // Create a dummy cmsMLU object using lcms API
    cmsMLU* mlu = cmsMLUalloc(NULL, 1);
    if (!mlu) return 0;

    // Test cmsMLUdup
    cmsMLU* dup = cmsMLUdup(mlu);
    if (dup) {
        cmsMLUfree(dup);
    }

    // Prepare language and country codes
    char LanguageCode[3] = { Data[0], Data[1], '\0' };
    char CountryCode[3] = { Data[2], Data[3], '\0' };

    // Ensure the Data is null-terminated for string operations
    char* utf8String = (char*)malloc(Size - 4 + 1);
    if (!utf8String) {
        cmsMLUfree(mlu);
        return 0;
    }
    memcpy(utf8String, Data + 4, Size - 4);
    utf8String[Size - 4] = '\0';

    // Test cmsMLUsetUTF8
    cmsMLUsetUTF8(mlu, LanguageCode, CountryCode, utf8String);

    // Test cmsMLUgetTranslation
    char ObtainedLanguage[3], ObtainedCountry[3];
    cmsMLUgetTranslation(mlu, LanguageCode, CountryCode, ObtainedLanguage, ObtainedCountry);

    // Test cmsMLUsetWide
    wchar_t WideString[4] = { L'A', L'B', L'C', L'\0' };
    cmsMLUsetWide(mlu, LanguageCode, CountryCode, WideString);

    // Test cmsMLUsetASCII
    cmsMLUsetASCII(mlu, LanguageCode, CountryCode, utf8String);

    // Test cmsDictAddEntry
    cmsHANDLE hDict = cmsDictAlloc(NULL);
    if (hDict) {
        cmsDictAddEntry(hDict, WideString, WideString, mlu, mlu);
        cmsDictFree(hDict);
    }

    free(utf8String);
    cmsMLUfree(mlu);
    return 0;
}