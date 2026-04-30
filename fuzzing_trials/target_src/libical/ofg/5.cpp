#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include string.h for memcpy

extern "C" {
    #include <libical/ical.h> // Assuming the correct path for libical headers
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create a valid icalproperty
    if (size < 1) {
        return 0;
    }

    // Initialize the library
    icalerror_clear_errno();

    // Create a temporary string from the input data
    char *temp = (char *)malloc(size + 1);
    if (!temp) {
        return 0;
    }
    memcpy(temp, data, size);
    temp[size] = '\0';

    // Create a new icalproperty from the string
    icalproperty *prop = icalproperty_new_from_string(temp);
    free(temp);

    // If the property is successfully created, call the function-under-test
    if (prop != NULL) {
        const char *queryname = icalproperty_get_queryname(prop);

        // Optionally, do something with the queryname, like logging or further checks
        // For now, we simply ensure the function is called
    }

    // Clean up
    if (prop != NULL) {
        icalproperty_free(prop);
    }

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

    LLVMFuzzerTestOneInput_5(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
