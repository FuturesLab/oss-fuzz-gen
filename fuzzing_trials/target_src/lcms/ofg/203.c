#include <stdint.h>
#include <stddef.h>
#include <lcms2.h> // Include the Little CMS library header

// Function signature to be fuzzed
int _cmsLCMScolorSpace(cmsColorSpaceSignature signature);

int LLVMFuzzerTestOneInput_203(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a cmsColorSpaceSignature
    if (size < sizeof(cmsColorSpaceSignature)) {
        return 0;
    }

    // Extract a cmsColorSpaceSignature from the input data
    cmsColorSpaceSignature signature = *(const cmsColorSpaceSignature *)data;

    // Call the function-under-test with the extracted signature
    int result = _cmsLCMScolorSpace(signature);

    // Use the result to avoid compiler optimizations that might skip the function call
    (void)result;

    return 0;
}