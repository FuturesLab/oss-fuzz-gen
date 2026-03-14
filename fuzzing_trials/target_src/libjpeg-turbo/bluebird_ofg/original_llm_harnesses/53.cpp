#include <cstdint>  // For uint8_t
#include <cstddef>  // For size_t

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0; // Ensure there is enough data to extract three integers
    }

    // Extract three integers from the input data
    int componentID = data[0]; // Use the first byte as the component ID
    int width = data[1];       // Use the second byte as the width
    int subsamp = data[2];     // Use the third byte as the subsampling

    // Call the function under test with the extracted parameters
    int height = tjPlaneHeight(componentID, width, subsamp);

    (void)height; // Use the result to avoid unused variable warning

    return 0;
}