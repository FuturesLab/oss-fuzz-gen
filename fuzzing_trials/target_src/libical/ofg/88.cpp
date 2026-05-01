#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to create a string
    if (size == 0) {
        return 0;
    }

    // Create a string from the input data
    char *ical_str = (char *)malloc(size + 1);
    if (!ical_str) {
        return 0;
    }
    memcpy(ical_str, data, size);
    ical_str[size] = '\0';

    // Parse the string into an icalcomponent
    icalcomponent *comp = icalparser_parse_string(ical_str);
    free(ical_str);

    if (comp == NULL) {
        return 0;
    }

    // Map the first byte of data to a valid icalproperty_method
    icalproperty_method method = ICAL_METHOD_NONE;
    if (size > 0) {
        method = static_cast<icalproperty_method>(data[0] % ICAL_METHOD_NONE);
    }

    // Call the function-under-test
    icalcomponent_set_method(comp, method);

    // Clean up
    icalcomponent_free(comp);

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

    LLVMFuzzerTestOneInput_88(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
