#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_414(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsToneCurve *inputCurve = NULL;
    cmsToneCurve *reversedCurve = NULL;
    cmsContext context = cmsCreateContext(NULL, NULL);
    
    // Check if size is sufficient to create a tone curve
    if (size < sizeof(cmsUInt16Number)) {
        return 0;
    }

    // Create a tone curve using the input data
    cmsUInt16Number *curveData = (cmsUInt16Number *)malloc(size);
    if (curveData == NULL) {
        return 0;
    }

    for (size_t i = 0; i < size / sizeof(cmsUInt16Number); i++) {
        curveData[i] = data[i % size];
    }

    inputCurve = cmsBuildTabulatedToneCurve16(context, size / sizeof(cmsUInt16Number), curveData);

    // Ensure inputCurve is not NULL
    if (inputCurve != NULL) {
        // Call the function-under-test
        reversedCurve = cmsReverseToneCurve(inputCurve);
        
        // Free the reversed curve if it was successfully created
        if (reversedCurve != NULL) {
            cmsFreeToneCurve(reversedCurve);
        }

        // Free the input curve
        cmsFreeToneCurve(inputCurve);
    }

    // Free allocated resources
    free(curveData);
    cmsDeleteContext(context);

    return 0;
}