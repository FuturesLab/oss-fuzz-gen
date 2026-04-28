#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/icalcomponent.h>
    #include <libical/icalerror.h>
}

extern "C" int LLVMFuzzerTestOneInput_287(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid string
    if (size == 0) return 0;

    // Initialize the icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *description = (char *)malloc(size + 1);
    if (description == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(description, data, size);
    description[size] = '\0';

    // Call the function-under-test
    icalcomponent_set_description(component, description);

    // Additional operations to increase code coverage
    const char *retrieved_description = icalcomponent_get_description(component);
    if (retrieved_description) {
        // Dummy operation to simulate further processing
        (void)strlen(retrieved_description);
    }

    // Clean up
    free(description);
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

    LLVMFuzzerTestOneInput_287(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
