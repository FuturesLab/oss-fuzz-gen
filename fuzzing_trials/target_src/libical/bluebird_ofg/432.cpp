#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_432(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient to create a valid null-terminated string
    if (size == 0 || data[size - 1] != '\0') {
        return 0;
    }

    // Create an icalproperty from the input data
    icalproperty *property = icalproperty_new_from_string((const char *)data);

    // Check if the property was created successfully
    if (property != NULL) {
        // Call the function-under-test
        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalproperty_get_url with icalproperty_get_itipversion
        const char *url = icalproperty_get_itipversion(property);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR

        // Optionally, you can perform some checks or use the url
        // For example, just print it if it's not NULL
        if (url != NULL) {
            // Normally, you wouldn't print in a fuzzing harness, but this is just for demonstration
            // printf("URL: %s\n", url);
        }

        // Free the icalproperty
        icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_432(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
