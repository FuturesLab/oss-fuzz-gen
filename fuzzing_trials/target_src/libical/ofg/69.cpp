#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *str = (char *)malloc(size + 1);
    if (str == NULL) {
        return 0;
    }

    // Copy data into the string and null-terminate it
    memcpy(str, data, size);
    str[size] = '\0';

    // Create a new icalproperty object
    icalproperty *prop = icalproperty_new_from_string(str);

    // Free the allocated string memory
    free(str);

    if (prop != NULL) {
        // Call the function-under-test
        const char *encoding = icalproperty_get_xlicmimeencoding(prop);

        // Perform any necessary checks or operations with the result
        if (encoding != NULL) {
            // Example: Print the encoding (not needed for fuzzing, but for demonstration)
            printf("Encoding: %s\n", encoding);
        }

        // Free the icalproperty object
        icalproperty_free(prop);
    }

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

    LLVMFuzzerTestOneInput_69(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
