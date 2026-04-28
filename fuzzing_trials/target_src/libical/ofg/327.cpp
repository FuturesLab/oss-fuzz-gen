#include <libical/ical.h>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_327(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *ical_str = static_cast<char*>(malloc(size + 1));
    assert(ical_str != NULL);
    memcpy(ical_str, data, size);
    ical_str[size] = '\0';

    // Parse the string into an icalproperty
    icalproperty *prop = icalproperty_new_from_string(ical_str);
    if (prop != NULL) {
        // Call the function-under-test
        int result = icalproperty_get_pollwinner(prop);

        // Clean up the property
        icalproperty_free(prop);
    }

    // Clean up the allocated string
    free(ical_str);

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

    LLVMFuzzerTestOneInput_327(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
