#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> // Include for malloc and free
#include <string.h> // Include for memcpy

// Wrap all C headers and function declarations in extern "C"
extern "C" {
    #include "/src/libical/src/libical/icalproperty.h" // Include the correct libical header for icalproperty

    // Function signature for the function-under-test
    int icalproperty_get_response(const icalproperty *);
    icalproperty* icalproperty_new_from_string(const char*);
    void icalproperty_free(icalproperty*);
}

extern "C" int LLVMFuzzerTestOneInput_455(const uint8_t *data, size_t size) {
    // Create a dummy icalproperty object from the input data
    // Assuming the input data is a string, convert it to a null-terminated string
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0;
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    icalproperty *prop = icalproperty_new_from_string(inputString);

    // Only proceed if prop is successfully created
    if (prop != NULL) {
        // Call the function-under-test with the dummy icalproperty object
        int response = icalproperty_get_response(prop);

        // Clean up
        icalproperty_free(prop);
    }

    free(inputString);

    // Return zero to indicate success
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

    LLVMFuzzerTestOneInput_455(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
