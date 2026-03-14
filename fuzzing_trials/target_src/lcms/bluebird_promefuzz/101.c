#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

static void WriteDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_101(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) return 0;

    cmsContext context = NULL;
    cmsUInt32Number nItems = *((cmsUInt32Number *)Data);
    Data += sizeof(cmsUInt32Number);
    Size -= sizeof(cmsUInt32Number);

    cmsMLU *mlu = cmsMLUalloc(context, nItems);
    if (mlu == NULL) return 0;

    // Fuzz cmsMLUdup
    cmsMLU *mluDup = cmsMLUdup(mlu);
    if (mluDup != NULL) {
        cmsMLUfree(mluDup);
    }

    // Fuzz cmsMLUtranslationsCount
    cmsUInt32Number translationsCount = cmsMLUtranslationsCount(mlu);

    // Fuzz cmsMLUgetASCII
    char languageCode[3] = "en";
    char countryCode[3] = "US";
    char buffer[256];
    cmsMLUgetASCII(mlu, languageCode, countryCode, buffer, sizeof(buffer));

    // Fuzz cmsMLUgetUTF8
    cmsMLUgetUTF8(mlu, languageCode, countryCode, buffer, sizeof(buffer));

    // Write data to a dummy file if needed
    WriteDummyFile(Data, Size);

    cmsMLUfree(mlu);

    return 0;
}