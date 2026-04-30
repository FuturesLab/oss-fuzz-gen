#include <stdint.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    // Create a dummy icalcomponent object for fuzzing
    icalcomponent *component = icalcomponent_new(ICAL_NO_COMPONENT);

    // Ensure the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Call the function-under-test
    const char *result = icalcomponent_get_x_name(component);

    // Use the result in some way to prevent optimization out
    if (result != NULL) {
        // Print the result length (for debugging purposes)
        size_t result_length = strlen(result);
        (void)result_length; // Suppress unused variable warning
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_161(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
