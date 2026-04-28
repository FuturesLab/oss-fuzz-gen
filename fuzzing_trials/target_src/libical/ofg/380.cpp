#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_380(const uint8_t *data, size_t size) {
    // Initialize the iCalendar library
    icalerror_set_error_state(ICAL_MALFORMEDDATA_ERROR, ICAL_ERROR_NONFATAL);

    // Ensure we have enough data to create a valid string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Create a new icalproperty object from the input data
    icalproperty *prop = icalproperty_new_from_string(inputData);
    if (prop != NULL) {
        // Call the function under test
        const char *result = icalproperty_get_patchdelete(prop);

        // Use the result to prevent it from being optimized away
        if (result != NULL) {
            // Simply print the result length
            size_t resultLength = strlen(result);
            (void)resultLength; // Suppress unused variable warning
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

    LLVMFuzzerTestOneInput_380(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
