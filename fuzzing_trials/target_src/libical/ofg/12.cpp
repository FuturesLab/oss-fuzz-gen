#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

extern "C" {
    // Assuming the function signature from the library
    typedef enum icalproperty_transp {
        ICAL_TRANSP_OPAQUE,
        ICAL_TRANSP_TRANSPARENT,
        ICAL_TRANSP_NONE
    } icalproperty_transp;

    icalproperty_transp icalproperty_string_to_transp(const char *);
}

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated before passing to the function
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0; // Exit early if memory allocation fails
    }
    
    memcpy(inputString, data, size);
    inputString[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalproperty_transp transp = icalproperty_string_to_transp(inputString);

    // Clean up
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

    LLVMFuzzerTestOneInput_12(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
