#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_279(const uint8_t *data, size_t size) {
    // Initialize TIFF pointer
    TIFF *tiff = TIFFOpen("/tmp/fuzzfileXXXXXX", "w");
    if (!tiff) {
        return 0;
    }

    // Ensure data size is sufficient for creating strings
    if (size < 2) {
        TIFFClose(tiff);
        return 0;
    }

    // Create non-null strings from data
    size_t str1_len = data[0] % (size - 1) + 1;
    size_t str2_len = data[1] % (size - str1_len - 1) + 1;

    char *str1 = (char *)malloc(str1_len + 1);
    char *str2 = (char *)malloc(str2_len + 1);

    if (!str1 || !str2) {
        free(str1);
        free(str2);
        TIFFClose(tiff);
        return 0;
    }

    memcpy(str1, data + 2, str1_len);
    memcpy(str2, data + 2 + str1_len, str2_len);

    str1[str1_len] = '\0';
    str2[str2_len] = '\0';

    // Call the function-under-test
    TIFFErrorExtR(tiff, str1, str2);

    // Clean up
    free(str1);
    free(str2);
    TIFFClose(tiff);

    return 0;
}