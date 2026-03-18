#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_375(const uint8_t *data, size_t size) {
    cmsHANDLE handle = cmsIT8Alloc(NULL);
    if (handle == NULL || size < 3) {
        return 0;
    }

    // Split the input data into three parts for the three string parameters
    size_t part_size = size / 3;
    size_t remainder = size % 3;

    char *str1 = (char *)malloc(part_size + 1);
    char *str2 = (char *)malloc(part_size + 1);
    char *str3 = (char *)malloc(part_size + remainder + 1);

    if (str1 == NULL || str2 == NULL || str3 == NULL) {
        cmsIT8Free(handle);
        free(str1);
        free(str2);
        free(str3);
        return 0;
    }

    strncpy(str1, (const char *)data, part_size);
    str1[part_size] = '\0';

    strncpy(str2, (const char *)(data + part_size), part_size);
    str2[part_size] = '\0';

    strncpy(str3, (const char *)(data + 2 * part_size), part_size + remainder);
    str3[part_size + remainder] = '\0';

    // Call the function-under-test
    cmsBool result = cmsIT8SetPropertyMulti(handle, str1, str2, str3);

    // Clean up
    cmsIT8Free(handle);
    free(str1);
    free(str2);
    free(str3);

    return 0;
}