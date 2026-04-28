#include <libical/ical.h>
#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_1257(const uint8_t *data, size_t size) {
    // Initialize the icalproperty object
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);

    // Ensure that the data is not null and has a reasonable size
    if (data != nullptr && size > 0) {
        // Copy the data into a null-terminated string
        char *inputData = new char[size + 1];
        memcpy(inputData, data, size);
        inputData[size] = '\0';

        // Set the property name using the fuzzed data
        icalproperty_set_x_name(property, inputData);

        // Call the function under test
        char *propertyName = icalproperty_get_property_name_r(property);

        // Clean up
        delete[] inputData;
        icalproperty_free(property);

        // If propertyName is not null, free it
        if (propertyName != nullptr) {
            icalmemory_free_buffer(propertyName);
        }
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

    LLVMFuzzerTestOneInput_1257(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
