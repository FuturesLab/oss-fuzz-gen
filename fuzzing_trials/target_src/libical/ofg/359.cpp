#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy and strlen

extern "C" {
    #include <libical/ical.h> // Assuming the correct path for the libical header
}

extern "C" int LLVMFuzzerTestOneInput_359(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to be meaningful
    if (size < 1) {
        return 0;
    }

    // Create a string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Create a temporary icalproperty object
    icalproperty *prop = icalproperty_new_from_string(inputData);
    if (prop != NULL) {
        // Call the function-under-test
        const char *result = icalproperty_get_grant(prop);

        // Use the result in some way to avoid compiler optimizations
        if (result != NULL) {
            volatile size_t result_len = strlen(result);
            (void)result_len; // Prevent unused variable warning
        }

        // Free the icalproperty object
        icalproperty_free(prop);
    }

    // Free the allocated input data
    free(inputData);

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

    LLVMFuzzerTestOneInput_359(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
