#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

static cmsHANDLE CreateDummyIT8Handle() {
    // This function should create a dummy IT8 handle for testing purposes.
    // In a real scenario, this would be replaced by a proper initialization.
    return cmsIT8Alloc(NULL); // Use library function to allocate a proper handle
}

static void DestroyDummyIT8Handle(cmsHANDLE hIT8) {
    // Free the IT8 handle using the library's function
    cmsIT8Free(hIT8);
}

int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Not enough data to proceed

    // Create a dummy IT8 handle
    cmsHANDLE hIT8 = CreateDummyIT8Handle();
    if (!hIT8) return 0;

    // Prepare input strings by splitting the data
    size_t halfSize = Size / 2;
    char *input1 = (char *)malloc(halfSize + 1);
    char *input2 = (char *)malloc(Size - halfSize + 1);

    if (!input1 || !input2) {
        DestroyDummyIT8Handle(hIT8);
        free(input1);
        free(input2);
        return 0;
    }

    memcpy(input1, Data, halfSize);
    input1[halfSize] = '\0';

    memcpy(input2, Data + halfSize, Size - halfSize);
    input2[Size - halfSize] = '\0';

    // Call the target functions with the prepared inputs
    cmsIT8FindDataFormat(hIT8, input1);
    cmsIT8SetDataDbl(hIT8, input1, input2, (cmsFloat64Number)0.0);
    cmsIT8SetPropertyDbl(hIT8, input1, (cmsFloat64Number)0.0);
    cmsIT8SetPropertyUncooked(hIT8, input1, input2);
    cmsIT8SetIndexColumn(hIT8, input1);

    // Save to a dummy file
    cmsIT8SaveToFile(hIT8, "./dummy_file");

    // Cleanup
    DestroyDummyIT8Handle(hIT8);
    free(input1);
    free(input2);

    return 0;
}