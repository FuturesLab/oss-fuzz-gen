#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid icalcomponent
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *ical_string = static_cast<char *>(malloc(size + 1));
    if (ical_string == nullptr) {
        return 0;
    }
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Convert the string into an icalcomponent
    icalcomponent *comp = icalparser_parse_string(ical_string);
    free(ical_string);

    if (comp != nullptr) {
        // Call the function under test
        const char *relcalid = icalcomponent_get_relcalid(comp);

        // Use the result in some way to prevent optimizations from removing the call
        if (relcalid) {
            // For example, print it if needed or perform other operations
            // printf("%s\n", relcalid);
        }

        // Clean up
        icalcomponent_free(comp);
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

    LLVMFuzzerTestOneInput_122(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
