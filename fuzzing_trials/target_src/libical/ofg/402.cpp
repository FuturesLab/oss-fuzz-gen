#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/icalproperty.h>
}

extern "C" int LLVMFuzzerTestOneInput_402(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the null-terminated string
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0;
    }

    // Copy data to inputString and null-terminate it
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_new_relatedto(inputString);

    // Additional operations to increase code coverage
    if (property != NULL) {
        // Attempt to retrieve the related-to property value
        const char *relatedToValue = icalproperty_get_relatedto(property);
        if (relatedToValue != NULL) {
            // Perform a simple operation to utilize the retrieved value
            size_t len = strlen(relatedToValue);
            if (len > 0) {
                // Print the length of the related-to value (for debug purposes, can be removed)
                // printf("Related-to value length: %zu\n", len);
            }
        }
        icalproperty_free(property);
    }

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

    LLVMFuzzerTestOneInput_402(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
