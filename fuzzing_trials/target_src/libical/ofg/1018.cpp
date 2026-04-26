#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1018(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for creating a string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputStr = (char *)malloc(size + 1);
    if (inputStr == NULL) {
        return 0;
    }
    memcpy(inputStr, data, size);
    inputStr[size] = '\0';

    // Determine the kind of icalvalue to create
    icalvalue_kind kind = ICAL_ANY_VALUE; // Use a default or appropriate kind

    // Create an icalvalue from the input string
    icalvalue *value = icalvalue_new_from_string(kind, inputStr);

    // Check if the icalvalue is valid
    if (value != NULL) {
        bool isValid = icalvalue_is_valid(value);

        // Clean up
        icalvalue_free(value);
    }

    // Free the allocated string
    free(inputStr);

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

    LLVMFuzzerTestOneInput_1018(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
