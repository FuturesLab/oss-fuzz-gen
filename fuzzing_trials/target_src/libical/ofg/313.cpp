#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Wrap the inclusion of C headers and functions in extern "C"
extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_313(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to safely pass as a C string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0; // Return if memory allocation fails
    }
    memcpy(input, data, size);
    input[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    struct icaltimetype result = icaltime_from_string(input);

    // Free the allocated memory
    free(input);

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

    LLVMFuzzerTestOneInput_313(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
