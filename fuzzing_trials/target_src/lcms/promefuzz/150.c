// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsMLUalloc at cmsnamed.c:33:19 in lcms2.h
// cmsMLUsetUTF8 at cmsnamed.c:368:19 in lcms2.h
// cmsMLUdup at cmsnamed.c:430:19 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
// cmsMLUsetUTF8 at cmsnamed.c:368:19 in lcms2.h
// cmsMLUsetASCII at cmsnamed.c:336:19 in lcms2.h
// cmsMLUgetTranslation at cmsnamed.c:663:26 in lcms2.h
// cmsMLUsetWide at cmsnamed.c:413:20 in lcms2.h
// cmsDictAlloc at cmsnamed.c:1090:21 in lcms2.h
// cmsDictAddEntry at cmsnamed.c:1137:19 in lcms2.h
// cmsDictFree at cmsnamed.c:1101:16 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include "lcms2.h"

static cmsMLU* create_dummy_mlu() {
    cmsMLU* mlu = cmsMLUalloc(NULL, 1);
    if (mlu) {
        cmsMLUsetUTF8(mlu, "en", "US", "Dummy");
    }
    return mlu;
}

int LLVMFuzzerTestOneInput_150(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0; // Ensure we have enough data for language and country codes

    cmsMLU* mlu = create_dummy_mlu();
    if (!mlu) return 0;

    // Test cmsMLUdup
    cmsMLU* mlu_dup = cmsMLUdup(mlu);
    if (mlu_dup) {
        cmsMLUfree(mlu_dup);
    }

    // Test cmsMLUsetUTF8
    char LanguageCode[3] = { (char)Data[0], (char)Data[1], '\0' };
    char CountryCode[3] = { (char)Data[2], (char)Data[3], '\0' };

    // Ensure UTF8String is null-terminated
    size_t utf8StringSize = Size - 4;
    char* UTF8String = (char*)malloc(utf8StringSize + 1);
    if (UTF8String) {
        memcpy(UTF8String, Data + 4, utf8StringSize);
        UTF8String[utf8StringSize] = '\0';
        cmsMLUsetUTF8(mlu, LanguageCode, CountryCode, UTF8String);

        // Test cmsMLUsetASCII
        cmsMLUsetASCII(mlu, LanguageCode, CountryCode, UTF8String);

        free(UTF8String);
    }

    // Test cmsMLUgetTranslation
    char ObtainedLanguage[3] = {0};
    char ObtainedCountry[3] = {0};
    cmsMLUgetTranslation(mlu, LanguageCode, CountryCode, ObtainedLanguage, ObtainedCountry);

    // Test cmsMLUsetWide
    wchar_t WideString[] = L"WideString";
    cmsMLUsetWide(mlu, LanguageCode, CountryCode, WideString);

    // Test cmsDictAddEntry
    cmsHANDLE hDict = cmsDictAlloc(NULL);
    if (hDict) {
        cmsDictAddEntry(hDict, WideString, WideString, mlu, mlu);
        cmsDictFree(hDict);
    }

    // Clean up
    cmsMLUfree(mlu);

    return 0;
}