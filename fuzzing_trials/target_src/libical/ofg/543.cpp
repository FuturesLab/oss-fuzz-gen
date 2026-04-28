#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_543(const uint8_t *data, size_t size) {
    // Initialize variables
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    char *x_name = nullptr;

    // Ensure size is non-zero and data is not NULL
    if (size > 0 && data != nullptr) {
        // Allocate memory for x_name and copy data into it
        x_name = (char *)malloc(size + 1);
        if (x_name != nullptr) {
            memcpy(x_name, data, size);
            x_name[size] = '\0';  // Null-terminate the string

            // Call the function-under-test
            icalcomponent_set_x_name(component, x_name);

            // Free allocated memory
            free(x_name);
        }
    }

    // Clean up
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_543(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
