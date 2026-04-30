#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1353(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a string
    if (size == 0) return 0;

    // Create a null-terminated string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) return 0;
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Create a new icalproperty from the input data
    icalproperty *prop = icalproperty_new_from_string(inputData);

    // Ensure the property is not NULL before proceeding
    if (prop != NULL) {
        // Call the function-under-test
        const char *recurLimit = icalproperty_get_recurlimit(prop);

        // Optionally, we can do something with recurLimit here
        // For now, we just ensure it's used to avoid compiler warnings
        if (recurLimit != NULL) {
            // Do nothing, just a placeholder
        }

        // Free the created property
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

    LLVMFuzzerTestOneInput_1353(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
