#include <stdint.h>
#include <stddef.h>

// Include libical headers within extern "C" block
extern "C" {
    #include <libical/ical.h>
}

// Correctly define the enumeration type for the method
extern "C" {
    // Function-under-test
    void icalproperty_set_method(icalproperty *prop, icalproperty_method method);
}

extern "C" int LLVMFuzzerTestOneInput_837(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a method value
    if (size < 1) {
        return 0;
    }

    // Initialize variables
    icalproperty *prop = icalproperty_new(ICAL_METHOD_PROPERTY);
    if (!prop) {
        return 0; // If property creation fails, exit early
    }

    // Use the first byte of data to determine the method
    icalproperty_method method = static_cast<icalproperty_method>(data[0] % (ICAL_METHOD_X + 1));

    // Call the function-under-test
    icalproperty_set_method(prop, method);

    // Additional operations to ensure code coverage
    icalproperty_method retrieved_method = icalproperty_get_method(prop);
    if (retrieved_method != method) {
        // Handle discrepancy if needed
    }

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

    LLVMFuzzerTestOneInput_837(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
