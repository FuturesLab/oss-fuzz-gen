#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

// Fuzzing function
int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty and has enough bytes for at least one cmsUInt16Number
    if (size < sizeof(cmsUInt16Number)) {
        return 0; // Not enough data to proceed
    }

    // Calculate the number of cmsUInt16Number elements we can safely extract from the input data
    size_t numCodes = size / sizeof(cmsUInt16Number);

    // Limit the number of codes to cmsMAXCHANNELS as per the function's requirement
    if (numCodes > cmsMAXCHANNELS) {
        numCodes = cmsMAXCHANNELS;
    }

    // Allocate memory for the alarm codes
    cmsUInt16Number *alarmCodes = (cmsUInt16Number *)malloc(numCodes * sizeof(cmsUInt16Number));
    if (alarmCodes == NULL) {
        return 0; // Memory allocation failed
    }

    // Safely copy the data into alarmCodes, ensuring no buffer overflow occurs
    memcpy(alarmCodes, data, numCodes * sizeof(cmsUInt16Number));

    // Call the function under test with the correct number of codes
    cmsGetAlarmCodes(alarmCodes);

    // Free the allocated memory
    free(alarmCodes);

    return 0;
}