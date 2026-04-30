#include <cstdint>
#include <cstdlib>
#include <cstring>

// Wrap C headers and function declarations in extern "C"
extern "C" {
    #include <libical/ical.h> // Adjust the path based on the actual location of ical headers in the project

    // Include necessary C headers and function declarations here.
    const char *icalproperty_get_parameter_as_string(icalproperty *, const char *);
}

extern "C" int LLVMFuzzerTestOneInput_1322(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract a non-empty string.
    if (size < 1) {
        return 0;
    }

    // Create a dummy icalproperty object.
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Allocate memory for a parameter name and ensure it's null-terminated.
    char *param_name = static_cast<char *>(malloc(size + 1));
    if (param_name == NULL) {
        icalproperty_free(property);
        return 0;
    }
    memcpy(param_name, data, size);
    param_name[size] = '\0';

    // Call the function-under-test.
    const char *result = icalproperty_get_parameter_as_string(property, param_name);

    // Clean up.
    free(param_name);
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_1322(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
