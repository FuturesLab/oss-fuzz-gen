// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsIT8Alloc at cmscgats.c:1454:22 in lcms2.h
// cmsIT8Free at cmscgats.c:1170:16 in lcms2.h
// cmsIT8GetProperty at cmscgats.c:1578:23 in lcms2.h
// cmsIT8DefineDblFormat at cmscgats.c:3041:16 in lcms2.h
// cmsIT8GetSheetType at cmscgats.c:1508:23 in lcms2.h
// cmsIT8GetPropertyMulti at cmscgats.c:1600:23 in lcms2.h
// cmsIT8GetPatchName at cmscgats.c:2955:23 in lcms2.h
// cmsIT8GetData at cmscgats.c:2862:23 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

#define DUMMY_FILE "./dummy_file"

static cmsHANDLE createDummyIT8Handle() {
    return cmsIT8Alloc(NULL);
}

static void destroyDummyIT8Handle(cmsHANDLE hIT8) {
    cmsIT8Free(hIT8);
}

int LLVMFuzzerTestOneInput_164(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsHANDLE hIT8 = createDummyIT8Handle();
    if (!hIT8) return 0;

    // Ensure the input data is treated as a null-terminated string
    char* propertyKey = (char*)malloc(Size + 1);
    if (!propertyKey) {
        destroyDummyIT8Handle(hIT8);
        return 0;
    }
    memcpy(propertyKey, Data, Size);
    propertyKey[Size] = '\0';

    // Test cmsIT8GetProperty
    const char* propertyValue = cmsIT8GetProperty(hIT8, propertyKey);
    if (propertyValue) {
        printf("Property Value: %s\n", propertyValue);
    }

    // Test cmsIT8DefineDblFormat
    cmsIT8DefineDblFormat(hIT8, propertyKey);

    // Test cmsIT8GetSheetType
    const char* sheetType = cmsIT8GetSheetType(hIT8);
    if (sheetType) {
        printf("Sheet Type: %s\n", sheetType);
    }

    // Test cmsIT8GetPropertyMulti
    const char* multiPropertyValue = cmsIT8GetPropertyMulti(hIT8, propertyKey, propertyKey);
    if (multiPropertyValue) {
        printf("Multi Property Value: %s\n", multiPropertyValue);
    }

    // Test cmsIT8GetPatchName
    char buffer[256];
    const char* patchName = cmsIT8GetPatchName(hIT8, (int)Data[0], buffer);
    if (patchName) {
        printf("Patch Name: %s\n", patchName);
    }

    // Test cmsIT8GetData
    const char* dataValue = cmsIT8GetData(hIT8, propertyKey, propertyKey);
    if (dataValue) {
        printf("Data Value: %s\n", dataValue);
    }

    free(propertyKey);
    destroyDummyIT8Handle(hIT8);
    return 0;
}