#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_832(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to be used for a string
    if (size == 0) {
        return 0;
    }

    // Create a new icalproperty instance with a specific property kind
    icalproperty *property = icalproperty_new(ICAL_SUMMARY_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Use the input data as a string, ensuring it's null-terminated
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        icalproperty_free(property);
        return 0;
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function-under-test
    icalproperty_set_summary(property, inputString);

    // Clean up
    free(inputString);
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_832(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
