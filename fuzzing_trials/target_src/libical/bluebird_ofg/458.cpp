#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_458(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid icalproperty
    if (size < 1) {
        return 0;
    }

    // Create a string from the input data
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Parse the input data into an icalproperty
    icalproperty *prop = icalproperty_new_from_string(input);
    if (prop != NULL) {
        // Call the function-under-test
        int percent_complete = icalproperty_get_percentcomplete(prop);

        // Clean up
        icalproperty_free(prop);
    }

    free(input);
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

    LLVMFuzzerTestOneInput_458(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
