#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for malloc and free
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Assuming the library header file
}

extern "C" int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to safely use it as a C-string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0; // Exit if memory allocation fails
    }

    memcpy(input, data, size);
    input[size] = '\0'; // Null-terminate the input

    // Call the function-under-test
    icalrecurrencetype_weekday result = icalrecur_string_to_weekday(input);

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

    LLVMFuzzerTestOneInput_143(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
