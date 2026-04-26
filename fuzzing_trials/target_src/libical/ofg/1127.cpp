#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy and strlen

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1127(const uint8_t *data, size_t size) {
    // Initialize the library
    icalproperty *prop = nullptr;

    // Ensure the data is not empty
    if (size > 0) {
        // Create a temporary buffer to hold the data
        char *buffer = new char[size + 1];
        memcpy(buffer, data, size);
        buffer[size] = '\0'; // Null-terminate the string

        // Parse the buffer into an icalproperty
        prop = icalproperty_new_from_string(buffer);

        // Clean up the buffer
        delete[] buffer;

        // If the property is successfully created, call the function-under-test
        if (prop != nullptr) {
            const char *restriction = icalproperty_get_restriction(prop);

            // Use the result in some way to prevent compiler optimizations
            if (restriction) {
                // Do something with restriction, like logging or further processing
                // Here we just check its length to interact with it
                size_t restriction_length = strlen(restriction);
                (void)restriction_length; // Suppress unused variable warning
            }

            // Clean up the icalproperty
            icalproperty_free(prop);
        }
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

    LLVMFuzzerTestOneInput_1127(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
