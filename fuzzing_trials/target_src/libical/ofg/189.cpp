#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_189(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the icalproperty
    icalproperty *property = icalproperty_new(ICAL_XLICMIMEOPTINFO_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *mime_info = (char *)malloc(size + 1);
    if (mime_info == NULL) {
        icalproperty_free(property);
        return 0;
    }
    memcpy(mime_info, data, size);
    mime_info[size] = '\0';

    // Call the function under test
    icalproperty_set_xlicmimeoptinfo(property, mime_info);

    // Additional operations to ensure code coverage
    const char *retrieved_mime_info = icalproperty_get_xlicmimeoptinfo(property);
    if (retrieved_mime_info != NULL) {
        // Perform a simple check to increase code coverage
        if (strcmp(mime_info, retrieved_mime_info) == 0) {
            // Do something trivial to ensure this code path is hit
            (void)retrieved_mime_info;
        }
    }

    // Attempt to parse the mime_info to increase code coverage
    icalcomponent *comp = icalparser_parse_string(mime_info);
    if (comp != NULL) {
        // Perform operations on the component to increase code coverage
        icalcomponent_free(comp);
    }

    // Clean up
    free(mime_info);
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_189(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
