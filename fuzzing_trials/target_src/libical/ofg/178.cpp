#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Corrected include path for libical
}

extern "C" int LLVMFuzzerTestOneInput_178(const uint8_t *data, size_t size) {
    // Initialize an icalproperty object from the input data
    icalproperty *prop = nullptr;

    // Ensure the data is not empty and create an icalproperty from it
    if (size > 0) {
        // Create a temporary buffer to hold the data as a string
        char *buffer = new char[size + 1];
        memcpy(buffer, data, size);
        buffer[size] = '\0'; // Null-terminate the string

        // Try to decode the buffer into an icalproperty
        prop = icalproperty_new_from_string(buffer);

        // Clean up the buffer
        delete[] buffer;
    }

    if (prop != nullptr) {
        // Call the function-under-test
        const char *result = icalproperty_get_patchtarget(prop);

        // Optionally, do something with the result (e.g., print or log it)
        // but avoid any side effects that might interfere with fuzzing

        // Clean up the icalproperty object
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

    LLVMFuzzerTestOneInput_178(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
