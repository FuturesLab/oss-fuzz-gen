#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include this header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_179(const uint8_t *data, size_t size) {
    icalproperty *prop;
    const char *result;

    // Check if size is sufficient to create a valid icalproperty
    if (size < 1) {
        return 0;
    }

    // Create a temporary string from the input data
    char *input_data = (char *)malloc(size + 1);
    if (!input_data) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0'; // Null-terminate the string

    // Create an icalproperty from the input data
    prop = icalproperty_new_from_string(input_data);
    free(input_data);

    if (prop == NULL) {
        return 0;
    }

    // Call the function-under-test
    result = icalproperty_get_patchtarget(prop);

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

    LLVMFuzzerTestOneInput_179(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
