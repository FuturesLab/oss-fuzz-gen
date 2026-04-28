#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_310(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to safely create a string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Convert the input data to an icalcomponent
    icalcomponent *component = icalparser_parse_string(input);
    if (component != NULL) {
        // Call the function-under-test
        char *icalString = icalcomponent_as_ical_string(component);

        // Free the returned string if not NULL
        if (icalString != NULL) {
            free(icalString);
        }

        // Free the icalcomponent
        icalcomponent_free(component);
    }

    // Free the input buffer
    free(input);

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

    LLVMFuzzerTestOneInput_310(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
