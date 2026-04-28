#include <stdint.h>
#include <stddef.h>
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1057(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a property
    if (size < 1) {
        return 0;
    }

    // Use the first byte of data to determine the type of property to create
    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0] % ICAL_NO_PROPERTY);

    // Create an icalproperty of the determined kind
    icalproperty *property = icalproperty_new(kind);

    // Check if property creation was successful
    if (property == NULL) {
        return 0;
    }

    // Optionally, set some property values using the remaining data
    if (size > 1) {
        // Use remaining data to set property values
        // For example, if the property is a string type, set a string value
        // This is a simple example, actual implementation may vary
        char *value = new char[size];
        memcpy(value, data + 1, size - 1);
        value[size - 1] = '\0';  // Null-terminate the string

        // Assuming the property can accept a string value
        icalproperty_set_value(property, icalvalue_new_string(value));

        // Clean up allocated memory
        delete[] value;
    }

    // Call the function-under-test
    struct icaldurationtype duration = icalproperty_get_estimatedduration(property);

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

    LLVMFuzzerTestOneInput_1057(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
