#include <libical/ical.h>
#include <cstdint>
#include <cstring>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_439(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *content_type = new char[size + 1];
    memcpy(content_type, data, size);
    content_type[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_xlicmimecontenttype(content_type, nullptr);

    // Check if the property was created and print a debug message
    if (prop != nullptr) {
        std::cout << "Property created: " << icalproperty_as_ical_string(prop) << std::endl;
        icalproperty_free(prop);
    } else {
        std::cout << "Property creation failed for content type: " << content_type << std::endl;
    }

    delete[] content_type;

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

    LLVMFuzzerTestOneInput_439(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
