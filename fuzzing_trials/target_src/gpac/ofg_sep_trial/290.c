#include <stdint.h>
#include <stdlib.h>
#include <stdio.h> // Include for sscanf and atoi
#include <gpac/isomedia.h> // Include for GF_ISOFile and related functions

int LLVMFuzzerTestOneInput_290(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract all required parameters
    if (size < sizeof(uint32_t) * 8 + sizeof(int32_t) * 2) {
        return 0;
    }

    // Initialize the parameters for the function-under-test
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL); // Properly initialize GF_ISOFile
    if (movie == NULL) {
        return 0;
    }

    uint32_t trackNumber = *((uint32_t *)data);
    uint32_t StreamDescriptionIndex = *((uint32_t *)(data + sizeof(uint32_t)));
    uint32_t cleanApertureWidthN = *((uint32_t *)(data + sizeof(uint32_t) * 2));
    uint32_t cleanApertureWidthD = *((uint32_t *)(data + sizeof(uint32_t) * 3));
    uint32_t cleanApertureHeightN = *((uint32_t *)(data + sizeof(uint32_t) * 4));
    uint32_t cleanApertureHeightD = *((uint32_t *)(data + sizeof(uint32_t) * 5));
    int32_t horizOffN = *((int32_t *)(data + sizeof(uint32_t) * 6));
    uint32_t horizOffD = *((uint32_t *)(data + sizeof(uint32_t) * 7));
    int32_t vertOffN = *((int32_t *)(data + sizeof(uint32_t) * 8));
    uint32_t vertOffD = *((uint32_t *)(data + sizeof(uint32_t) * 9));

    // Call the function-under-test
    gf_isom_set_clean_aperture(movie, trackNumber, StreamDescriptionIndex, 
                               cleanApertureWidthN, cleanApertureWidthD, 
                               cleanApertureHeightN, cleanApertureHeightD, 
                               horizOffN, horizOffD, vertOffN, vertOffD);

    // Clean up
    gf_isom_close(movie);

    return 0;
}