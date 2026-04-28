#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_586(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (!inputData) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Convert the input data to an icalvalue
    // Assuming icalvalue_kind is needed, choose a default kind, e.g., ICAL_STRING_VALUE
    icalvalue *originalValue = icalvalue_new_from_string(ICAL_STRING_VALUE, inputData);
    free(inputData);

    if (originalValue == NULL) {
        return 0;
    }

    // Clone the icalvalue
    icalvalue *clonedValue = icalvalue_clone(originalValue);

    // Clean up
    icalvalue_free(originalValue);
    if (clonedValue != NULL) {
        icalvalue_free(clonedValue);
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

    LLVMFuzzerTestOneInput_586(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
