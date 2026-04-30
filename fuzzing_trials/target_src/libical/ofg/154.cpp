#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid icalproperty
    if (size < 1) {
        return 0;
    }

    // Create a dummy icalproperty to pass to the function
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);

    // Ensure the property is not null
    if (!property) {
        return 0;
    }

    // Modify the property based on input data to increase code coverage
    icalproperty_set_x(property, reinterpret_cast<const char*>(data));

    // Call the function-under-test
    icalproperty_pollmode pollmode = icalproperty_get_pollmode(property);

    // Correct enum value for comparison
    if (pollmode == ICAL_POLLMODE_NONE) {
        // Do something with pollmode, e.g., print or log
    }

    // Clean up
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

    LLVMFuzzerTestOneInput_154(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
