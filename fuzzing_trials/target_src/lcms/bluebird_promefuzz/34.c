#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

#define MAX_ROW 10
#define MAX_COL 10

static cmsHANDLE createValidIT8Handle() {
    // This function should create and return a valid IT8 handle
    // The actual implementation will depend on the lcms library's API
    // For illustration, we assume a function `cmsIT8Alloc` exists
    return cmsIT8Alloc(NULL);
}

static void destroyValidIT8Handle(cmsHANDLE hIT8) {
    if (hIT8) {
        cmsIT8Free(hIT8);
    }
}

static char* safeString(const uint8_t* Data, size_t Size, size_t offset) {
    if (offset >= Size) return strdup("default");
    size_t maxLength = Size - offset;
    char* str = (char*)malloc(maxLength + 1);
    if (!str) return strdup("default");
    memcpy(str, &Data[offset], maxLength);
    str[maxLength] = '\0'; // Ensure null-termination
    return str;
}

int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsHANDLE hIT8 = createValidIT8Handle();
    if (!hIT8) return 0;

    // Fuzz cmsIT8SetDataRowCol
    int row = Data[0] % MAX_ROW;
    int col = (Size > 1) ? Data[1] % MAX_COL : 0;
    char* val = safeString(Data, Size, 2);
    cmsIT8SetDataRowCol(hIT8, row, col, val);
    free(val);

    // Fuzz cmsIT8SetPropertyHex
    char* cProp = safeString(Data, Size, 3);
    cmsUInt32Number hexVal = (Size > 7) ? *(cmsUInt32Number*)&Data[4] : 0xDEADBEEF;
    cmsIT8SetPropertyHex(hIT8, cProp, hexVal);
    free(cProp);

    // Fuzz cmsIT8GetDataRowCol
    const char* dataValue = cmsIT8GetDataRowCol(hIT8, row, col);

    // Fuzz cmsIT8EnumDataFormat
    char **sampleNames = NULL;
    int numSamples = cmsIT8EnumDataFormat(hIT8, &sampleNames);
    if (sampleNames) {
        for (int i = 0; i < numSamples; i++) {
            free(sampleNames[i]);
        }
        free(sampleNames);
    }

    // Fuzz cmsIT8SetDataFormat
    char* sampleFormat = safeString(Data, Size, 8);
    cmsIT8SetDataFormat(hIT8, row, sampleFormat);
    free(sampleFormat);

    // Fuzz cmsIT8SetPropertyMulti
    char* key = safeString(Data, Size, 9);
    char* subKey = safeString(Data, Size, 10);
    char* buffer = safeString(Data, Size, 11);
    cmsIT8SetPropertyMulti(hIT8, key, subKey, buffer);
    free(key);
    free(subKey);
    free(buffer);

    // Cleanup
    destroyValidIT8Handle(hIT8);

    return 0;
}