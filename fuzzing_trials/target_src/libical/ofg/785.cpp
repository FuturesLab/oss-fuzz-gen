#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

extern "C" {
    #include <libical/ical.h> // Assuming the correct path for the ical library
    struct icaltriggertype icaltriggertype_from_string(const char *);
}

extern "C" int LLVMFuzzerTestOneInput_785(const uint8_t *data, size_t size) {
    // Ensure that the data is null-terminated to be used as a string
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0; // Memory allocation failed
    }
    
    memcpy(inputString, data, size);
    inputString[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    struct icaltriggertype result = icaltriggertype_from_string(inputString);

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

    LLVMFuzzerTestOneInput_785(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
