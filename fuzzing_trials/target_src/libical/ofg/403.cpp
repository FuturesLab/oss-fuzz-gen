#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Adjust the include path as necessary for your project
}

extern "C" int LLVMFuzzerTestOneInput_403(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated and not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *inputString = new char[size + 1];
    if (inputString == nullptr) {
        return 0;
    }

    // Copy data to inputString and null-terminate it
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_new_relatedto(inputString);

    // Clean up
    if (property != nullptr) {
        icalproperty_free(property);
    }
    delete[] inputString;

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

    LLVMFuzzerTestOneInput_403(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
