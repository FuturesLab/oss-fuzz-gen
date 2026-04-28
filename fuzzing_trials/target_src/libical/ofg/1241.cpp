#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_1241(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *ical_str = (char *)malloc(size + 1);
    if (ical_str == NULL) {
        return 0;
    }

    // Copy the input data into the string and null-terminate it
    memcpy(ical_str, data, size);
    ical_str[size] = '\0';

    // Parse the string into an icalproperty object
    icalproperty *prop = icalproperty_new_from_string(ical_str);

    // Ensure the property is not NULL
    if (prop != NULL) {
        // Call the function under test
        int param_count = icalproperty_count_parameters(prop);

        // Clean up the icalproperty object
        icalproperty_free(prop);
    }

    // Free the allocated string
    free(ical_str);

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

    LLVMFuzzerTestOneInput_1241(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
