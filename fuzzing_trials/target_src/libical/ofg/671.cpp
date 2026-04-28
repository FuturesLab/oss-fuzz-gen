#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>  // Assuming the correct path for the ical library
}

extern "C" int LLVMFuzzerTestOneInput_671(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a valid string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *ical_string = (char *)malloc(size + 1);
    if (ical_string == NULL) {
        return 0;
    }

    // Copy the data into the string and null-terminate it
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Create an icalproperty from the string
    icalproperty *prop = icalproperty_new_from_string(ical_string);

    // Free the allocated string memory
    free(ical_string);

    // If the property was successfully created, call the function-under-test
    if (prop != NULL) {
        struct icaltimetype dtstamp = icalproperty_get_dtstamp(prop);

        // Clean up the property
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

    LLVMFuzzerTestOneInput_671(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
