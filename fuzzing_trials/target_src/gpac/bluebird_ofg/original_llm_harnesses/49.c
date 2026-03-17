#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h> // Include the necessary header for GF_ISOFile

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for extracting parameters
    if (size < 44) {
        return 0;
    }

    // Initialize parameters for the function-under-test
    // Provide a temporary directory for the third argument
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, "/tmp"); // Use a library function to create the GF_ISOFile
    if (movie == NULL) {
        return 0; // Exit if file creation fails
    }

    // Extract parameters from the input data
    uint32_t trackNumber = *((uint32_t *)(data));
    uint32_t StreamDescriptionIndex = *((uint32_t *)(data + 4));
    uint32_t cleanApertureWidthN = *((uint32_t *)(data + 8));
    uint32_t cleanApertureWidthD = *((uint32_t *)(data + 12));
    uint32_t cleanApertureHeightN = *((uint32_t *)(data + 16));
    uint32_t cleanApertureHeightD = *((uint32_t *)(data + 20));
    int32_t horizOffN = *((int32_t *)(data + 24));
    uint32_t horizOffD = *((uint32_t *)(data + 28));
    int32_t vertOffN = *((int32_t *)(data + 32));
    uint32_t vertOffD = *((uint32_t *)(data + 36));

    // Call the function-under-test
    gf_isom_set_clean_aperture(movie, trackNumber, StreamDescriptionIndex, cleanApertureWidthN, cleanApertureWidthD, cleanApertureHeightN, cleanApertureHeightD, horizOffN, horizOffD, vertOffN, vertOffD);

    // Close the file and free allocated resources
    gf_isom_close(movie);

    return 0;
}