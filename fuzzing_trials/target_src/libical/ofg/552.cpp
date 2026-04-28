#include <iostream>
#include <cstdint>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_552(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for icalproperty
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *locale = new char[size + 1];
    memcpy(locale, data, size);
    locale[size] = '\0';  // Null-terminate the string

    // Call the function under test
    icalproperty_set_defaultlocale(prop, locale);

    // Clean up
    icalproperty_free(prop);
    delete[] locale;

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

    LLVMFuzzerTestOneInput_552(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
