#include <stdint.h>
#include <stddef.h>
#include <cstring> // Include the necessary header for memcpy

extern "C" {
    #include <libical/ical.h> // Wrap libical includes in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_819(const uint8_t *data, size_t size) {
    // Use dynamic memory allocation to avoid variable length array
    char *prop_name = new char[size + 1];
    if (size > 0) {
        memcpy(prop_name, data, size);
    }
    prop_name[size] = '\0'; // Null-terminate the string

    // Create a dummy icalproperty for testing
    icalproperty *prop = icalproperty_new_from_string(prop_name);
    if (prop == NULL) {
        delete[] prop_name; // Clean up dynamically allocated memory
        return 0; // Exit if the property could not be created
    }

    // Call the function-under-test
    const char *source = icalproperty_get_source(prop);

    // Clean up
    icalproperty_free(prop);
    delete[] prop_name; // Clean up dynamically allocated memory

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

    LLVMFuzzerTestOneInput_819(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
