#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_245(const uint8_t *data, size_t size) {
    // Ensure that the data is null-terminated before treating it as a string
    if (size == 0) {
        return 0; // Exit if no data is provided
    }

    char *tzurl = (char *)malloc(size + 1);
    if (tzurl == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(tzurl, data, size);
    tzurl[size] = '\0'; // Null-terminate the string

    // Create a new icalproperty
    icalproperty *prop = icalproperty_new(ICAL_TZURL_PROPERTY);
    if (prop == NULL) {
        free(tzurl);
        return 0; // Exit if property creation fails
    }

    // Call the function-under-test
    icalproperty_set_tzurl(prop, tzurl);

    // Verify the property was set correctly
    const char *retrieved_tzurl = icalproperty_get_tzurl(prop);
    if (retrieved_tzurl != NULL && strcmp(retrieved_tzurl, tzurl) == 0) {
        // The function under test works as expected
    }

    // Clean up
    icalproperty_free(prop);
    free(tzurl);

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

    LLVMFuzzerTestOneInput_245(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
