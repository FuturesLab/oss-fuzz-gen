#include <cstdint>
#include <cstdlib>
#include <cstring>  // For memcpy

extern "C" {
    #include <libical/ical.h>  // Assuming the correct path for libical headers
}

extern "C" int LLVMFuzzerTestOneInput_1288(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a non-null string.
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data.
    char *inputString = static_cast<char *>(malloc(size + 1));
    if (!inputString) {
        return 0;
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function under test.
    icalproperty *property = icalproperty_vanew_multipart(inputString, nullptr);

    // Clean up.
    if (property != nullptr) {
        icalproperty_free(property);
    }
    free(inputString);

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

    LLVMFuzzerTestOneInput_1288(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
