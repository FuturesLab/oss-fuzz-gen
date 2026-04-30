#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "libical/ical.h" // Assume this is the correct header for icalrecur_string_to_skip
}

extern "C" int LLVMFuzzerTestOneInput_1182(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated for safe string operations
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0; // Memory allocation failed, exit early
    }

    memcpy(input, data, size);
    input[size] = '\0'; // Null-terminate the input

    // Call the function-under-test
    icalrecurrencetype_skip result = icalrecur_string_to_skip(input);

    // Clean up
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

    LLVMFuzzerTestOneInput_1182(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
