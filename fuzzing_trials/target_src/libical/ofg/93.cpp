#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include the necessary header for malloc and free

extern "C" {
    // Declare the function-under-test
    struct icaldurationtype {
        int is_neg;
        int weeks;
        int days;
        int hours;
        int minutes;
        int seconds;
    };

    struct icaldurationtype icaldurationtype_from_string(const char *);
}

extern "C" int LLVMFuzzerTestOneInput_93(const uint8_t *data, size_t size) {
    // Ensure that the input data is null-terminated for string processing
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0;
    }

    // Copy the input data to the string and null-terminate it
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function-under-test
    struct icaldurationtype duration = icaldurationtype_from_string(inputString);

    // Free the allocated memory
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

    LLVMFuzzerTestOneInput_93(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
