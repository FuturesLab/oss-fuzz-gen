#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to create a string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the string and ensure it's null-terminated
    char *tzname = (char *)malloc(size + 1);
    if (tzname == NULL) {
        return 0;
    }
    memcpy(tzname, data, size);
    tzname[size] = '\0';

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_TZNAME_PROPERTY);
    if (prop == NULL) {
        free(tzname);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_tzname(prop, tzname);

    // Verify the property was set correctly
    const char *retrieved_tzname = icalproperty_get_tzname(prop);
    if (retrieved_tzname != NULL && strcmp(retrieved_tzname, tzname) != 0) {
        // Handle unexpected result
    }

    // Additional verification to ensure the fuzz target is effective
    // This can be done by checking if the retrieved_tzname is not null
    // and has some expected properties (e.g., length, specific characters)
    if (retrieved_tzname != NULL) {
        // Check if the retrieved tzname is not empty
        if (strlen(retrieved_tzname) > 0) {
            // Further checks can be added here if needed
        }
    }

    // Clean up
    icalproperty_free(prop);
    free(tzname);

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

    LLVMFuzzerTestOneInput_82(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
