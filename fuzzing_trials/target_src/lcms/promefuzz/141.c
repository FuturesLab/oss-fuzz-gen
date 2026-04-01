// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsIT8Alloc at cmscgats.c:1454:22 in lcms2.h
// cmsIT8SetSheetType at cmscgats.c:1513:19 in lcms2.h
// cmsIT8Free at cmscgats.c:1170:16 in lcms2.h
// cmsIT8DefineDblFormat at cmscgats.c:3041:16 in lcms2.h
// cmsIT8SetSheetType at cmscgats.c:1513:19 in lcms2.h
// cmsIT8SetPropertyStr at cmscgats.c:1533:19 in lcms2.h
// cmsIT8SetIndexColumn at cmscgats.c:3025:19 in lcms2.h
// cmsstrcasecmp at cmserr.c:39:15 in lcms2.h
// cmsIT8GetPatchByName at cmscgats.c:2974:15 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "lcms2.h"

static cmsHANDLE createIT8Handle() {
    // Create a valid IT8 handle using the library's API
    cmsHANDLE hIT8 = cmsIT8Alloc(NULL);
    if (hIT8 != NULL) {
        cmsIT8SetSheetType(hIT8, "IT8.7/2");
    }
    return hIT8;
}

static void destroyIT8Handle(cmsHANDLE hIT8) {
    // Free the IT8 handle using the library's API
    if (hIT8 != NULL) {
        cmsIT8Free(hIT8);
    }
}

int LLVMFuzzerTestOneInput_141(const uint8_t *Data, size_t Size) {
    if (Size < 5) return 0; // Ensure there is enough data for partitioning

    cmsHANDLE hIT8 = createIT8Handle();
    if (hIT8 == NULL) return 0;

    // Use a portion of the data for each function call
    size_t partSize = Size / 5;

    // Ensure null-termination and avoid buffer overflow
    char patchName[256] = {0};
    char dblFormat[256] = {0};
    char sheetType[256] = {0};
    char propertyKey[256] = {0};
    char propertyValue[256] = {0};
    char sampleName[256] = {0};
    char string1[256] = {0};
    char string2[256] = {0};

    snprintf(patchName, sizeof(patchName), "%.*s", (int)partSize, Data);
    snprintf(dblFormat, sizeof(dblFormat), "%.*s", (int)partSize, Data + partSize);
    snprintf(sheetType, sizeof(sheetType), "%.*s", (int)partSize, Data + 2 * partSize);
    snprintf(propertyKey, sizeof(propertyKey), "%.*s", (int)partSize, Data + 3 * partSize);
    snprintf(propertyValue, sizeof(propertyValue), "%.*s", (int)partSize, Data + 4 * partSize);

    // Test cmsIT8DefineDblFormat
    cmsIT8DefineDblFormat(hIT8, dblFormat);

    // Test cmsIT8SetSheetType
    cmsIT8SetSheetType(hIT8, sheetType);

    // Test cmsIT8SetPropertyStr
    cmsIT8SetPropertyStr(hIT8, propertyKey, propertyValue);

    // Test cmsIT8SetIndexColumn
    cmsIT8SetIndexColumn(hIT8, sampleName);

    // Test cmsstrcasecmp
    snprintf(string1, sizeof(string1), "%.*s", (int)partSize, Data);
    snprintf(string2, sizeof(string2), "%.*s", (int)partSize, Data + partSize);
    cmsstrcasecmp(string1, string2);

    // Test cmsIT8GetPatchByName
    cmsIT8GetPatchByName(hIT8, patchName);

    destroyIT8Handle(hIT8);

    return 0;
}