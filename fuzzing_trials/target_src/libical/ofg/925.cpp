#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_925(const uint8_t *data, size_t size) {
    icalcomponent *vtimezone = NULL;
    char *result = NULL;

    // Ensure that size is not zero and data is not NULL
    if (size == 0 || data == NULL) {
        return 0;
    }

    // Create a string buffer from the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0;
    }
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalcomponent
    vtimezone = icalparser_parse_string(buffer);

    // Call the function-under-test
    if (vtimezone != NULL) {
        result = icaltimezone_get_tznames_from_vtimezone(vtimezone);

        // Free the result if not NULL
        if (result != NULL) {
            free(result);
        }

        // Free the icalcomponent
        icalcomponent_free(vtimezone);
    }

    // Free the buffer
    free(buffer);

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

    LLVMFuzzerTestOneInput_925(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
