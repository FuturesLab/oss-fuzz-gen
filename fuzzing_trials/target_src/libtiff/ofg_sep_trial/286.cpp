#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_286(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 3) {
        return 0;
    }

    // Create a TIFF object
    TIFF *tiff = TIFFOpen("/tmp/fuzz.tiff", "w");
    if (!tiff) {
        return 0;
    }

    // Prepare strings from the input data
    size_t str1_len = data[0] % size;
    size_t str2_len = data[1] % size;
    size_t str3_len = data[2] % size;

    char *str1 = (char *)malloc(str1_len + 1);
    char *str2 = (char *)malloc(str2_len + 1);
    char *str3 = (char *)malloc(str3_len + 1);

    if (!str1 || !str2 || !str3) {
        TIFFClose(tiff);
        free(str1);
        free(str2);
        free(str3);
        return 0;
    }

    memcpy(str1, data + 3, str1_len);
    memcpy(str2, data + 3 + str1_len, str2_len);
    memcpy(str3, data + 3 + str1_len + str2_len, str3_len);

    str1[str1_len] = '\0';
    str2[str2_len] = '\0';
    str3[str3_len] = '\0';

    // Call the function-under-test
    TIFFWarningExtR(tiff, str1, str2, str3);

    // Clean up
    TIFFClose(tiff);
    free(str1);
    free(str2);
    free(str3);

    return 0;
}