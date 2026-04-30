#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" {
    #include <string.h> // Include string.h for memcpy
}

extern "C" int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    // Initialize the library context
    icalcomponent *component = nullptr;

    // Ensure the size is sufficient to create a component
    if (size > 0) {
        // Create a temporary buffer to hold the data
        char *buffer = new char[size + 1];
        memcpy(buffer, data, size);
        buffer[size] = '\0'; // Null-terminate the buffer

        // Try to parse the data into an icalcomponent
        component = icalparser_parse_string(buffer);

        // Free the buffer
        delete[] buffer;
    }

    // Call the function-under-test
    if (component != nullptr) {
        icalcomponent_free(component);
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_98(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
