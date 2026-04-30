#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    // Initialize variables
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    char *x_name = nullptr;

    // Ensure the input size is sufficient to create a null-terminated string
    if (size > 0) {
        // Allocate memory for x_name and copy data into it
        x_name = (char *)malloc(size + 1);
        if (x_name != nullptr) {
            memcpy(x_name, data, size);
            x_name[size] = '\0'; // Null-terminate the string

            // Call the function-under-test
            icalcomponent_set_x_name(component, x_name);

            // Free the allocated memory for x_name
            free(x_name);
        }
    }

    // Clean up the component
    icalcomponent_free(component);

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

    LLVMFuzzerTestOneInput_81(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
