#include <cstddef>
#include <cstdint>
#include <iostream>

extern "C" {
    // Include the correct path for the turbojpeg.h header
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"

    // Function prototype from the library
    tjscalingfactor * tj3GetScalingFactors(int *numScalingFactors);
}

extern "C" int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
    // Initialize the number of scaling factors
    int numScalingFactors = 0;

    // Call the function-under-test
    tjscalingfactor *scalingFactors = tj3GetScalingFactors(&numScalingFactors);

    // Check if scalingFactors is not NULL and numScalingFactors is positive
    if (scalingFactors != nullptr && numScalingFactors > 0) {
        // Iterate over the scaling factors and print them for debugging
        for (int i = 0; i < numScalingFactors; ++i) {
            std::cout << "Scaling Factor " << i << ": "
                      << scalingFactors[i].num << "/"
                      << scalingFactors[i].denom << std::endl;
        }
    }

    return 0;
}