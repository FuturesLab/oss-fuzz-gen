#include <stdint.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_694(const uint8_t *data, size_t size) {
    // Initialize icalvalue and icalproperty
    icalvalue *value = icalvalue_new_from_string(ICAL_STRING_VALUE, "example");
    icalproperty *property = icalproperty_new_comment("example comment");

    // Ensure that both value and property are not NULL
    if (value != NULL && property != NULL) {
        // Call the function-under-test
        icalvalue_set_parent(value, property);
    }

    // Clean up
    if (value != NULL) {
        icalvalue_free(value);
    }
    if (property != NULL) {
        icalproperty_free(property);
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_694(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
