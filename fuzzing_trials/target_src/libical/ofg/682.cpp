#include <stdint.h>
#include <stdbool.h>
#include <stddef.h> // Include this for size_t

// Assuming the necessary declarations for icalproperty_kind and icalproperty_kind_is_valid
// are within the project but not in a header file named ical.h, we need to declare them here.

extern "C" {
    typedef enum {
        ICAL_NO_PROPERTY = 0, // Example value, replace with actual values from the project
        // ... other possible values for icalproperty_kind
    } icalproperty_kind;

    // Function-under-test
    bool icalproperty_kind_is_valid(const icalproperty_kind kind);
}

extern "C" int LLVMFuzzerTestOneInput_682(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to interpret as icalproperty_kind
    if (size < sizeof(icalproperty_kind)) {
        return 0;
    }

    // Interpret the input data as icalproperty_kind
    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0]);

    // Call the function-under-test
    bool is_valid = icalproperty_kind_is_valid(kind);

    // Use the result to avoid compiler optimizations
    (void)is_valid;

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

    LLVMFuzzerTestOneInput_682(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
