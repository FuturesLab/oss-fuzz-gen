#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1001(const uint8_t *data, size_t size) {
    // Initialize the icalproperty
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);

    // Ensure the data is large enough to be used meaningfully
    if (size > 0) {
        // Create a string from the input data
        char *inputStr = (char *)malloc(size + 1);
        if (inputStr == NULL) {
            icalproperty_free(prop);
            return 0;
        }
        memcpy(inputStr, data, size);
        inputStr[size] = '\0';

        // Set a property value using the input string
        icalproperty_set_comment(prop, inputStr);

        // Free the input string
        free(inputStr);
    }

    // Call the function-under-test
    const char *tzid = icalproperty_get_defaulttzid(prop);

    // Use the result (tzid) in some way, here we just ensure it's not NULL
    if (tzid != NULL) {
        // Do something with tzid, for now we just print it
        printf("Default TZID: %s\n", tzid);
    }

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

    LLVMFuzzerTestOneInput_1001(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
