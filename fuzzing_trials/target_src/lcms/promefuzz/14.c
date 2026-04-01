// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
// cmsMLUtranslationsCodes at cmsnamed.c:696:19 in lcms2.h
// cmsMLUgetWide at cmsnamed.c:629:27 in lcms2.h
// cmsMLUsetUTF8 at cmsnamed.c:368:19 in lcms2.h
// cmsMLUgetTranslation at cmsnamed.c:663:26 in lcms2.h
// cmsMLUsetWide at cmsnamed.c:413:20 in lcms2.h
// cmsMLUsetASCII at cmsnamed.c:336:19 in lcms2.h
// cmsMLUalloc at cmsnamed.c:33:19 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include "lcms2.h"

static cmsMLU* createDummyMLU() {
    return cmsMLUalloc(NULL, 0);
}

static void freeDummyMLU(cmsMLU* mlu) {
    if (mlu) {
        cmsMLUfree(mlu);
    }
}

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 5) return 0; // Ensure there is enough data for LanguageCode and CountryCode

    cmsMLU* mlu = createDummyMLU();
    if (!mlu) return 0;

    char LanguageCode[3] = {0};
    char CountryCode[3] = {0};
    wchar_t WideString[256] = {0};

    cmsUInt32Number idx = Data[0] % 10;
    memcpy(LanguageCode, Data + 1, 2);
    memcpy(CountryCode, Data + 3, 2);

    cmsMLUtranslationsCodes(mlu, idx, LanguageCode, CountryCode);

    cmsMLUgetWide(mlu, LanguageCode, CountryCode, WideString, 256);

    // Ensure null-termination for UTF8String
    char* UTF8String = (char*)malloc(Size + 1);
    if (UTF8String) {
        memcpy(UTF8String, Data, Size);
        UTF8String[Size] = '\0';
        cmsMLUsetUTF8(mlu, LanguageCode, CountryCode, UTF8String);
        free(UTF8String);
    }

    cmsMLUgetTranslation(mlu, LanguageCode, CountryCode, LanguageCode, CountryCode);

    cmsMLUsetWide(mlu, LanguageCode, CountryCode, WideString);

    // Ensure null-termination for ASCIIString
    char* ASCIIString = (char*)malloc(Size + 1);
    if (ASCIIString) {
        memcpy(ASCIIString, Data, Size);
        ASCIIString[Size] = '\0';
        cmsMLUsetASCII(mlu, LanguageCode, CountryCode, ASCIIString);
        free(ASCIIString);
    }

    freeDummyMLU(mlu);
    return 0;
}