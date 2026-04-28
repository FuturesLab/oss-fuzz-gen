#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1030(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a valid icalproperty
    if (size == 0) {
        return 0;
    }

    // Create a temporary string from the input data
    char *tempStr = (char *)malloc(size + 1);
    if (tempStr == NULL) {
        return 0;
    }
    memcpy(tempStr, data, size);
    tempStr[size] = '\0';

    // Create an icalproperty from the string
    icalproperty *prop = icalproperty_new_from_string(tempStr);

    // Free the temporary string
    free(tempStr);

    if (prop == NULL) {
        return 0;
    }

    // Call the function-under-test
    const char *result = icalproperty_get_storesexpanded(prop);

    // Use the result in some way to prevent compiler optimizations from removing the call
    if (result != NULL) {
        // Just a dummy operation to use the result
        volatile size_t dummy = strlen(result);
        (void)dummy;
    }

    // Free the icalproperty
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_1030(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
