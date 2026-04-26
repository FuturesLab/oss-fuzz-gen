#include <stdint.h>
#include <stddef.h>

// Ensure standard libraries are included before project-specific ones
extern "C" {
    #include <libical/ical.h>
}

// Correct the enum type name to match the actual libical enumeration
extern "C" int LLVMFuzzerTestOneInput_248(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to derive a valid enumeration value
    if (size < sizeof(int)) {
        return 0;
    }

    // Map the input data to a valid enumeration value
    // Assuming icalproperty_method is an enum, and we use the first 4 bytes of data to create a value
    int enum_value = *(reinterpret_cast<const int*>(data));
    
    // Normalize the enum_value to fit within the range of valid enum values
    // Assuming the enum has a known range, for this example, let's say 0 to 10
    enum_value = enum_value % 11; // Adjust based on actual enum range

    // Cast the normalized value to the enum type
    icalproperty_method method = static_cast<icalproperty_method>(enum_value);

    // Call the function-under-test
    icalproperty *property = icalproperty_new_method(method);

    // Clean up if necessary
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

    LLVMFuzzerTestOneInput_248(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
