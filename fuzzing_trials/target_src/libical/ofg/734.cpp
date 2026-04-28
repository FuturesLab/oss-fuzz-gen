#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <libical/ical.h> // Correct path to the libical header

    // Function-under-test
    struct icaltimetype icalproperty_get_mindate(const icalproperty *);
}

extern "C" int LLVMFuzzerTestOneInput_734(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to create an icalproperty
    if (size < 1) {
        return 0; // Exit if the input is too small
    }

    // Initialize the icalproperty object with a specific property kind
    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0] % ICAL_NO_PROPERTY);
    icalproperty *prop = icalproperty_new(kind);

    if (prop == NULL) {
        return 0; // Exit if the property could not be created
    }

    // Call the function-under-test
    struct icaltimetype min_date = icalproperty_get_mindate(prop);

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

    LLVMFuzzerTestOneInput_734(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
