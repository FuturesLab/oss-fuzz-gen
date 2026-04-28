#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_835(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Convert input data to a string
    std::string input(reinterpret_cast<const char*>(data), size);

    // Create an icalproperty from the input data
    icalproperty *prop = icalproperty_new_from_string(input.c_str());

    // Check if the property was created successfully
    if (prop != nullptr) {
        // Call the function-under-test
        const char *uid = icalproperty_get_uid(prop);

        // Print the UID if it exists
        if (uid != nullptr) {
            std::cout << "UID: " << uid << std::endl;
        }

        // Free the property
        icalproperty_free(prop);
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

    LLVMFuzzerTestOneInput_835(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
