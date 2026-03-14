// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsIT8Alloc at cmscgats.c:1454:22 in lcms2.h
// cmsIT8Free at cmscgats.c:1170:16 in lcms2.h
// cmsIT8SetDataRowCol at cmscgats.c:2838:19 in lcms2.h
// cmsIT8SetDataRowColDbl at cmscgats.c:2848:19 in lcms2.h
// cmsIT8GetPatchByName at cmscgats.c:2974:15 in lcms2.h
// cmsIT8SetDataDbl at cmscgats.c:2940:19 in lcms2.h
// cmsIT8SetPropertyDbl at cmscgats.c:1543:19 in lcms2.h
// cmsIT8GetDataRowColDbl at cmscgats.c:2826:28 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2.h>

// Assuming there's a function to create a valid IT8 handle.
// This is a placeholder for an actual IT8 handle creation.
static cmsHANDLE createDummyIT8Handle() {
    // Properly allocate a dummy IT8 structure with expected size
    return cmsIT8Alloc(NULL);
}

static void destroyDummyIT8Handle(cmsHANDLE hIT8) {
    cmsIT8Free(hIT8);
}

int LLVMFuzzerTestOneInput_99(const uint8_t *Data, size_t Size) {
    cmsHANDLE hIT8 = createDummyIT8Handle();
    if (!hIT8) return 0;

    if (Size < 1) {
        destroyDummyIT8Handle(hIT8);
        return 0;
    }

    // Use the first byte to determine which function to call
    uint8_t choice = Data[0];
    Data++;
    Size--;

    switch (choice % 6) {
        case 0: {
            // Fuzz cmsIT8SetDataRowCol
            if (Size < sizeof(int) * 2 + 1) break;
            int row = *(int*)Data;
            int col = *(int*)(Data + sizeof(int));
            const char* val = (const char*)(Data + 2 * sizeof(int));
            size_t valLen = strnlen(val, Size - 2 * sizeof(int));
            if (valLen >= Size - 2 * sizeof(int)) break; // Ensure null-termination
            cmsIT8SetDataRowCol(hIT8, row, col, val);
            break;
        }
        case 1: {
            // Fuzz cmsIT8SetDataRowColDbl
            if (Size < sizeof(int) * 2 + sizeof(cmsFloat64Number)) break;
            int row = *(int*)Data;
            int col = *(int*)(Data + sizeof(int));
            cmsFloat64Number val = *(cmsFloat64Number*)(Data + 2 * sizeof(int));
            cmsIT8SetDataRowColDbl(hIT8, row, col, val);
            break;
        }
        case 2: {
            // Fuzz cmsIT8GetPatchByName
            if (Size < 1) break;
            const char* patchName = (const char*)Data;
            size_t patchNameLen = strnlen(patchName, Size);
            if (patchNameLen >= Size) break; // Ensure null-termination
            cmsIT8GetPatchByName(hIT8, patchName);
            break;
        }
        case 3: {
            // Fuzz cmsIT8SetDataDbl
            if (Size < 1 + sizeof(cmsFloat64Number)) break;
            const char* patch = (const char*)Data;
            size_t patchLen = strnlen(patch, Size);
            if (patchLen + 1 >= Size) break;
            const char* sample = (const char*)(Data + patchLen + 1);
            size_t sampleLen = strnlen(sample, Size - patchLen - 1);
            if (patchLen + sampleLen + 2 + sizeof(cmsFloat64Number) > Size) break;
            cmsFloat64Number val = *(cmsFloat64Number*)(Data + patchLen + sampleLen + 2);
            cmsIT8SetDataDbl(hIT8, patch, sample, val);
            break;
        }
        case 4: {
            // Fuzz cmsIT8SetPropertyDbl
            if (Size < 1 + sizeof(cmsFloat64Number)) break;
            const char* prop = (const char*)Data;
            size_t propLen = strnlen(prop, Size);
            if (propLen + 1 + sizeof(cmsFloat64Number) > Size) break;
            cmsFloat64Number val = *(cmsFloat64Number*)(Data + propLen + 1);
            cmsIT8SetPropertyDbl(hIT8, prop, val);
            break;
        }
        case 5: {
            // Fuzz cmsIT8GetDataRowColDbl
            if (Size < sizeof(int) * 2) break;
            int row = *(int*)Data;
            int col = *(int*)(Data + sizeof(int));
            cmsIT8GetDataRowColDbl(hIT8, row, col);
            break;
        }
    }

    destroyDummyIT8Handle(hIT8);
    return 0;
}