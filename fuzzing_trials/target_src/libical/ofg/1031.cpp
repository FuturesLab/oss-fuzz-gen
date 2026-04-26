#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1031(const uint8_t *data, size_t size) {
    // Initialize a new icalproperty
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);

    // Ensure that the data is not NULL and has sufficient size
    if (data != NULL && size > 0) {
        // Convert the input data to a string
        char *inputData = (char *)malloc(size + 1);
        if (inputData == NULL) {
            return 0; // Handle memory allocation failure
        }
        memcpy(inputData, data, size);
        inputData[size] = '\0';

        // Set the property value
        icalproperty_set_value(prop, icalvalue_new_string(inputData));

        // Free the allocated memory for inputData
        free(inputData);
    }

    // Call the function-under-test
    const char *result = icalproperty_get_storesexpanded(prop);

    // Clean up
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

    LLVMFuzzerTestOneInput_1031(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
