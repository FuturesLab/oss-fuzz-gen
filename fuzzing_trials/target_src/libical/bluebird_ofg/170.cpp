#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include this library for memcpy

extern "C" {
    #include "/src/libical/src/libical/icalproperty.h" // Include the correct header for libical
}

extern "C" int LLVMFuzzerTestOneInput_170(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid icalproperty
    if (size == 0) {
        return 0;
    }

    // Create a temporary string buffer to hold the data
    char *buffer = new char[size + 1];
    if (buffer == nullptr) {
        return 0;
    }

    // Copy the data into the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Create an icalproperty from the buffer
    icalproperty *property = icalproperty_new_from_string(buffer);

    // Ensure property is not NULL before calling the function
    if (property != nullptr) {
        // Call the function-under-test
        struct icalreqstattype status = icalproperty_get_requeststatus(property);

        // Clean up the icalproperty
        icalproperty_free(property);
    }

    // Clean up the buffer
    delete[] buffer;

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

    LLVMFuzzerTestOneInput_170(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
