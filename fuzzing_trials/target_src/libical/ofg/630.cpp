#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <cstring> // Added for memcpy

extern "C" {
    #include "libical/ical.h" // Assuming the necessary header for icalvalue_isa is in libical
}

extern "C" int LLVMFuzzerTestOneInput_630(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to create a valid icalvalue
    if (size < 1) {
        return 0;
    }

    // Create a temporary buffer to hold the data
    char *buffer = static_cast<char *>(malloc(size + 1));
    if (buffer == nullptr) {
        return 0;
    }

    // Copy the data into the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Determine a default kind for the icalvalue
    icalvalue_kind kind = ICAL_STRING_VALUE; // Assuming a default kind, adjust as necessary

    // Create an icalvalue from the buffer
    icalvalue *value = icalvalue_new_from_string(kind, buffer);
    if (value != nullptr) {
        // Call the function-under-test
        kind = icalvalue_isa(value);

        // Output the kind for debugging purposes
        std::cout << "icalvalue_kind: " << kind << std::endl;

        // Free the icalvalue
        icalvalue_free(value);
    }

    // Free the buffer
    free(buffer);

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

    LLVMFuzzerTestOneInput_630(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
