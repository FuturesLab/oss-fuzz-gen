#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1056(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid icalproperty
    if (size < 1) {
        return 0;
    }

    // Create an icalproperty from the input data
    // Since icalproperty_new_from_string expects a null-terminated string,
    // we need to ensure the data is null-terminated.
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Create a new icalproperty from the input data
    icalproperty *prop = icalproperty_new_from_string(input_data);

    // Ensure prop is not NULL before proceeding
    if (prop != NULL) {
        // Call the function under test
        struct icaldurationtype duration = icalproperty_get_estimatedduration(prop);

        // Clean up the icalproperty
        icalproperty_free(prop);
    }

    // Free the allocated memory for input_data
    free(input_data);

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

    LLVMFuzzerTestOneInput_1056(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
