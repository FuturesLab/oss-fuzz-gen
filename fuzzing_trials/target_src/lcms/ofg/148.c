#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>
#include <stdlib.h>  // Include for malloc and free

int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
    // Ensure there's enough data to initialize at least one cmsUInt16Number
    if (size < sizeof(cmsUInt16Number)) {
        return 0;
    }

    // Calculate the number of cmsUInt16Number elements we can create
    size_t num_elements = size / sizeof(cmsUInt16Number);

    // Allocate memory for cmsUInt16Number array using malloc
    cmsUInt16Number* alarmCodes = (cmsUInt16Number*)malloc(num_elements * sizeof(cmsUInt16Number));
    if (alarmCodes == NULL) {
        return 0;  // Handle memory allocation failure
    }

    // Copy data into the cmsUInt16Number array
    for (size_t i = 0; i < num_elements; ++i) {
        alarmCodes[i] = ((cmsUInt16Number*)data)[i];
    }

    // Call the function-under-test
    cmsSetAlarmCodes(alarmCodes);

    // Clean up using free
    free(alarmCodes);

    return 0;
}