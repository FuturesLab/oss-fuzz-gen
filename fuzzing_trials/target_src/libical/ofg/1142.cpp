#include <stddef.h>
#include <stdint.h>
#include <string.h> // Include for strlen function

extern "C" {
    #include <libical/ical.h> // Assuming the correct path for libical headers
}

extern "C" int LLVMFuzzerTestOneInput_1142(const uint8_t *data, size_t size) {
    // Initialize a dummy icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);

    // Ensure the property is not NULL
    if (prop == NULL) {
        return 0;
    }

    // Call the function-under-test
    const char *charset = icalproperty_get_defaultcharset(prop);

    // Use the charset in some way to avoid compiler optimizations removing it
    if (charset != NULL) {
        // For fuzzing purposes, we can just check the length
        size_t charset_length = strlen(charset);
        (void)charset_length; // Suppress unused variable warning
    }

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

    LLVMFuzzerTestOneInput_1142(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
