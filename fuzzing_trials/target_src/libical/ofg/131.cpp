#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    icalcomponent *component = nullptr;
    icaltimetype due_time;

    // Ensure the data is not empty and can be used to create a component
    if (size > 0) {
        // Create a temporary buffer to hold the data
        char *temp_buffer = new char[size + 1];
        memcpy(temp_buffer, data, size);
        temp_buffer[size] = '\0'; // Null-terminate the buffer

        // Parse the data into an icalcomponent
        component = icalparser_parse_string(temp_buffer);

        // Clean up the temporary buffer
        delete[] temp_buffer;
    }

    // Ensure the component is not NULL before calling the function-under-test
    if (component != nullptr) {
        // Call the function-under-test
        due_time = icalcomponent_get_due(component);

        // Free the component after use
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

    LLVMFuzzerTestOneInput_131(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
