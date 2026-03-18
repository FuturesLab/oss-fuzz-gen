#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcpy
#include <lcms2.h>

int LLVMFuzzerTestOneInput_235(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for cmsCIELab structure
    if (size < sizeof(cmsCIELab)) {
        return 0;
    }

    // Initialize variables
    cmsUInt16Number encodedLab[3];
    cmsCIELab lab;

    // Copy data into the cmsCIELab structure
    memcpy(&lab, data, sizeof(cmsCIELab));

    // Call the function under test
    cmsFloat2LabEncoded(encodedLab, &lab);

    return 0;
}