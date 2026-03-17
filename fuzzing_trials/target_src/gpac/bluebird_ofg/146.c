#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h" // Assuming this is the correct header file for the function

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract all parameters
    if (size < sizeof(uint32_t) * 9 + sizeof(int32_t) * 2) {
        return 0;
    }

    // Initialize a new GF_ISOFile object
    // Provide a non-null file name and a temporary directory for the function
    const char *fileName = "temp_file.mp4";
    const char *tmp_dir = "/tmp";
    GF_ISOFile *movie = gf_isom_open(fileName, GF_ISOM_OPEN_WRITE, tmp_dir);

    if (!movie) {
        return 0; // If allocation fails, exit gracefully
    }

    // Initialize variables for function parameters using the input data
    uint32_t trackNumber = *(uint32_t *)(data);
    uint32_t StreamDescriptionIndex = *(uint32_t *)(data + sizeof(uint32_t));
    uint32_t cleanApertureWidthN = *(uint32_t *)(data + sizeof(uint32_t) * 2);
    uint32_t cleanApertureWidthD = *(uint32_t *)(data + sizeof(uint32_t) * 3);
    uint32_t cleanApertureHeightN = *(uint32_t *)(data + sizeof(uint32_t) * 4);
    uint32_t cleanApertureHeightD = *(uint32_t *)(data + sizeof(uint32_t) * 5);
    int32_t horizOffN = *(int32_t *)(data + sizeof(uint32_t) * 6);
    uint32_t horizOffD = *(uint32_t *)(data + sizeof(uint32_t) * 6 + sizeof(int32_t));
    int32_t vertOffN = *(int32_t *)(data + sizeof(uint32_t) * 7 + sizeof(int32_t));
    uint32_t vertOffD = *(uint32_t *)(data + sizeof(uint32_t) * 7 + sizeof(int32_t) * 2);

    // Call the function-under-test
    gf_isom_set_clean_aperture(movie, trackNumber, StreamDescriptionIndex, cleanApertureWidthN, cleanApertureWidthD, cleanApertureHeightN, cleanApertureHeightD, horizOffN, horizOffD, vertOffN, vertOffD);

    // Close the GF_ISOFile to free resources
    gf_isom_close(movie);

    return 0;
}