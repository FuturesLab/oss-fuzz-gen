#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_436(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for creating a valid icalproperty
    if (size == 0) {
        return 0;
    }

    // Create a string from the input data
    char *ical_string = (char *)malloc(size + 1);
    if (!ical_string) {
        return 0;
    }
    memcpy(ical_string, data, size);
    ical_string[size] = '\0'; // Null-terminate the string

    // Convert the string to an icalproperty
    icalproperty *prop = icalproperty_new_from_string(ical_string);
    if (prop != NULL) {
        // Call the function-under-test
        const char *content_type = icalproperty_get_xlicmimecontenttype(prop);

        // Use the result to prevent optimization out
        if (content_type) {
            // Normally, you might log or use the content_type, but for fuzzing, we just ensure it's accessed
            (void)content_type;
        }

        // Clean up
        icalproperty_free(prop);
    }

    free(ical_string);
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

    LLVMFuzzerTestOneInput_436(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
