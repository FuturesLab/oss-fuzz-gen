#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    // Assuming the correct function declaration based on the project documentation
    typedef enum icalrecurrencetype_skip {
        ICAL_SKIP_NONE,
        ICAL_SKIP_BACKWARD,
        ICAL_SKIP_FORWARD,
        ICAL_SKIP_UNKNOWN
    } icalrecurrencetype_skip;

    icalrecurrencetype_skip icalrecur_string_to_skip(const char *);
}

extern "C" int LLVMFuzzerTestOneInput_1183(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated before passing it as a string
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0;  // Handle allocation failure
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    icalrecurrencetype_skip result = icalrecur_string_to_skip(inputString);

    // Free the allocated memory
    free(inputString);

    // Return 0 to indicate the fuzzer should continue
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

    LLVMFuzzerTestOneInput_1183(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
