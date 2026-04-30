#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" {
    // Assuming the function signature is part of the libical library
    void icalproperty_set_method(icalproperty *prop, icalproperty_method method);
}

extern "C" int LLVMFuzzerTestOneInput_836(const uint8_t *data, size_t size) {
    // Initialize the icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_METHOD_PROPERTY);

    // Ensure the data size is enough to extract a method value
    if (size < sizeof(icalproperty_method)) {
        icalproperty_free(prop);
        return 0;
    }

    // Extract a method from the data
    icalproperty_method method = static_cast<icalproperty_method>(data[0] % ICAL_METHOD_NONE);

    // Call the function-under-test
    icalproperty_set_method(prop, method);

    // Clean up
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_836(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
