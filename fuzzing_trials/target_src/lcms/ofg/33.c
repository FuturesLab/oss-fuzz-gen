#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <lcms2_plugin.h>

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    char *sampleData1;
    char *sampleData2;
    char *sampleData3;
    cmsBool result;

    // Initialize the handle
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure size is sufficient to split into three parts
    if (size < 3) {
        cmsIT8Free(handle);
        return 0;
    }

    // Allocate memory and copy data for the three strings
    sampleData1 = (char *)malloc(size / 3 + 1);
    sampleData2 = (char *)malloc(size / 3 + 1);
    sampleData3 = (char *)malloc(size / 3 + 1);

    if (sampleData1 == NULL || sampleData2 == NULL || sampleData3 == NULL) {
        free(sampleData1);
        free(sampleData2);
        free(sampleData3);
        cmsIT8Free(handle);
        return 0;
    }

    memcpy(sampleData1, data, size / 3);
    sampleData1[size / 3] = '\0';

    memcpy(sampleData2, data + size / 3, size / 3);
    sampleData2[size / 3] = '\0';

    memcpy(sampleData3, data + 2 * (size / 3), size / 3);
    sampleData3[size / 3] = '\0';

    // Call the function-under-test
    result = cmsIT8SetData(handle, sampleData1, sampleData2, sampleData3);

    // Clean up
    free(sampleData1);
    free(sampleData2);
    free(sampleData3);
    cmsIT8Free(handle);

    return 0;
}