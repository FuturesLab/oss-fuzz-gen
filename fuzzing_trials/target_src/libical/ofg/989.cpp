#include <stdint.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_989(const uint8_t *data, size_t size) {
    // Ensure there's enough data to process
    if (size < 1) {
        return 0;
    }

    // Define a set of possible icalproperty_transp values
    icalproperty_transp transp_values[] = {
        ICAL_TRANSP_OPAQUE,
        ICAL_TRANSP_TRANSPARENT,
        ICAL_TRANSP_NONE
    };

    // Use the first byte of data to select a transp value
    icalproperty_transp transp = transp_values[data[0] % (sizeof(transp_values) / sizeof(transp_values[0]))];

    // Call the function-under-test
    const char *result = icalproperty_transp_to_string(transp);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result) {
        volatile char c = result[0];
        (void)c;
    }

    // Additional function calls to increase code coverage
    // Create an icalproperty and set the transp value
    icalproperty *property = icalproperty_new_transp(transp);
    if (property) {
        // Serialize the property to a string
        const char *property_str = icalproperty_as_ical_string(property);
        if (property_str) {
            // Use the serialized string
            volatile char c = property_str[0];
            (void)c;
            free((void*)property_str); // Cast to void* to free const char*
        }
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

    LLVMFuzzerTestOneInput_989(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
