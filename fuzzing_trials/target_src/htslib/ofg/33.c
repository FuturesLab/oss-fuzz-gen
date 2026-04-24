#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/htslib/htslib/sam.h" // Correct path for sam_hdr_t and the function

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Initialize the parameters for the function-under-test
    sam_hdr_t *hdr = sam_hdr_init(); // Assuming sam_hdr_init initializes a sam_hdr_t object
    if (hdr == NULL) {
        return 0; // Fail gracefully if hdr cannot be initialized
    }

    // Ensure data is large enough to split into two non-NULL strings
    if (size < 2) {
        sam_hdr_destroy(hdr); // Clean up
        return 0;
    }

    // Split the data into two strings for the function parameters
    size_t mid = size / 2;
    char *str1 = (char *)malloc(mid + 1);
    char *str2 = (char *)malloc(size - mid + 1);

    if (str1 == NULL || str2 == NULL) {
        sam_hdr_destroy(hdr); // Clean up
        free(str1);
        free(str2);
        return 0;
    }

    memcpy(str1, data, mid);
    str1[mid] = '\0'; // Null-terminate the first string

    memcpy(str2, data + mid, size - mid);
    str2[size - mid] = '\0'; // Null-terminate the second string

    // Call the function-under-test
    int result = sam_hdr_change_HD(hdr, str1, str2);

    // Clean up
    free(str1);
    free(str2);
    sam_hdr_destroy(hdr);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_33(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
