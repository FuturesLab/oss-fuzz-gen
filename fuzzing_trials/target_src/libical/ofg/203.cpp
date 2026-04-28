#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_203(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputString = (char *)malloc(size + 1);
    if (!inputString) {
        return 0;
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Create an icalproperty from the string
    icalproperty *prop = icalproperty_new_from_string(inputString);

    // Check if the property was created successfully
    if (prop != NULL) {
        // Call the function-under-test
        const char *relatedTo = icalproperty_get_relatedto(prop);

        // Use the result in some way to avoid compiler optimizations
        if (relatedTo != NULL) {
            // Example usage: print the result
            printf("Related to: %s\n", relatedTo);
        }

        // Free the icalproperty
        icalproperty_free(prop);
    }

    // Free the allocated input string
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

    LLVMFuzzerTestOneInput_203(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
