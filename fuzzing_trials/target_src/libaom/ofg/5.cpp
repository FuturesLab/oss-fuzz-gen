#include <aom/aom_codec.h>
#include <aom/aom_decoder.h>
#include <aom/aom_encoder.h>
#include <cstddef> // For size_t
#include <cstdint> // For uint8_t

extern "C" {
    const char * aom_codec_iface_name(aom_codec_iface_t *);
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Declare and initialize the codec interface pointer
    aom_codec_iface_t *iface = nullptr;

    // Ensure that the data size is sufficient to create a valid codec interface
    // Since aom_codec_iface_t is an incomplete type, we cannot use sizeof on it.
    // Instead, we will check if the data is not null and has a reasonable size.
    if (size < 1) { // Adjusted to check for at least 1 byte of data
        return 0; // Not enough data to proceed
    }

    // Initialize the codec interface with the provided data
    iface = reinterpret_cast<aom_codec_iface_t*>(const_cast<uint8_t*>(data));

    // Call the function under test
    const char *iface_name = aom_codec_iface_name(iface);

    // Optionally, you can use iface_name for further processing or logging
    // For this fuzzing harness, we simply call the function to ensure it executes

    return 0;
}