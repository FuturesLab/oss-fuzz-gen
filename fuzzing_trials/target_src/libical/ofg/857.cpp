extern "C" {
    #include <libical/ical.h>
    #include <stdint.h>
    #include <stddef.h>
    #include <stdlib.h>
    #include <string.h>
}

extern "C" int LLVMFuzzerTestOneInput_857(const uint8_t *data, size_t size) {
    // Ensure the input data is not too small
    if (size < 1) return 0;

    // Initialize a string buffer with the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) return 0;
    memcpy(buffer, data, size);
    buffer[size] = '\0'; // Null-terminate the string

    // Create a temporary icalproperty object from the buffer
    icalproperty *prop = icalproperty_new_from_string(buffer);
    if (prop == NULL) {
        free(buffer);
        return 0;
    }

    // Call the function-under-test
    icalattach *attachment = icalproperty_get_image(prop);

    // Clean up
    if (attachment != NULL) {
        icalattach_unref(attachment);
    }
    icalproperty_free(prop);
    free(buffer);

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

    LLVMFuzzerTestOneInput_857(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
