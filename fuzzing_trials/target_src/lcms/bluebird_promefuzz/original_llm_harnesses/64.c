// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsIT8EnumProperties at cmscgats.c:2665:27 in lcms2.h
// cmsIT8SetPropertyHex at cmscgats.c:1553:19 in lcms2.h
// cmsIT8SaveToMem at cmscgats.c:2047:19 in lcms2.h
// cmsIT8SaveToMem at cmscgats.c:2047:19 in lcms2.h
// cmsIT8SetTable at cmscgats.c:1427:26 in lcms2.h
// cmsIT8EnumPropertyMulti at cmscgats.c:2700:27 in lcms2.h
// cmsIT8TableCount at cmscgats.c:2981:27 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

// Dummy function to simulate IT8 handle creation
static cmsHANDLE createDummyIT8Handle() {
    // Allocate a more realistic size for the IT8 structure
    cmsHANDLE handle = malloc(sizeof(struct { cmsUInt32Number nTable; cmsUInt32Number TablesCount; }));
    if (handle) {
        // Initialize the structure with some default values
        ((cmsUInt32Number*)handle)[0] = 0; // nTable
        ((cmsUInt32Number*)handle)[1] = 1; // TablesCount
    }
    return handle;
}

static void freeDummyIT8Handle(cmsHANDLE handle) {
    free(handle);
}

int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsHANDLE hIT8 = createDummyIT8Handle();
    if (!hIT8) return 0;

    // Fuzz cmsIT8EnumProperties
    char **propertyNames = NULL;
    cmsUInt32Number propertyCount = cmsIT8EnumProperties(hIT8, &propertyNames);
    if (propertyNames) {
        for (cmsUInt32Number i = 0; i < propertyCount; i++) {
            free(propertyNames[i]);
        }
        free(propertyNames);
    }

    // Fuzz cmsIT8SetPropertyHex
    const char *cProp = "TestProperty";
    cmsUInt32Number val = (cmsUInt32Number)Data[0];
    cmsIT8SetPropertyHex(hIT8, cProp, val);

    // Fuzz cmsIT8SaveToMem
    cmsUInt32Number bytesNeeded = 0;
    cmsIT8SaveToMem(hIT8, NULL, &bytesNeeded);
    if (bytesNeeded > 0) {
        void *memPtr = malloc(bytesNeeded);
        if (memPtr) {
            cmsIT8SaveToMem(hIT8, memPtr, &bytesNeeded);
            free(memPtr);
        }
    }

    // Fuzz cmsIT8SetTable
    cmsUInt32Number tableIndex = (cmsUInt32Number)(Data[0] % 10);
    cmsIT8SetTable(hIT8, tableIndex);

    // Fuzz cmsIT8EnumPropertyMulti
    const char **subpropertyNames = NULL;
    cmsIT8EnumPropertyMulti(hIT8, cProp, &subpropertyNames);
    if (subpropertyNames) {
        free(subpropertyNames);
    }

    // Fuzz cmsIT8TableCount
    cmsIT8TableCount(hIT8);

    freeDummyIT8Handle(hIT8);
    return 0;
}