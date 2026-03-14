#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Declare and initialize the variables needed for cmsSetAlarmCodesTHR
    cmsContext context = cmsCreateContext(NULL, NULL); // Create a valid context
    if (context == NULL) {
        return 0; // Exit if context creation fails
    }
    
    cmsUInt16Number alarmCodes[256]; // Array to hold alarm codes, increased size for robustness

    // Ensure there is data to read from
    if (size >= sizeof(cmsUInt16Number)) {
        // Copy data into the alarmCodes array, ensuring not to overflow
        size_t numCodes = size / sizeof(cmsUInt16Number);
        if (numCodes > 256) {
            numCodes = 256; // Limit to the size of the array
        }
        for (size_t i = 0; i < numCodes; i++) {
            alarmCodes[i] = ((cmsUInt16Number *)data)[i];
        }
    } else {
        // If not enough data, set a default value
        alarmCodes[0] = 0;
    }

    // Call the function-under-test
    cmsSetAlarmCodesTHR(context, alarmCodes);

    // Clean up the context
    cmsDeleteContext(context);

    return 0;
}