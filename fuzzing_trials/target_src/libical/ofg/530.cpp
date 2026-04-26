#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>  // Include for malloc and free

extern "C" {
    #include <libical/ical.h>  // Assuming the correct path for the ical library
}

extern "C" int LLVMFuzzerTestOneInput_530(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *related_to_str = (char *)malloc(size + 1);
    if (related_to_str == NULL) {
        return 0;
    }
    memcpy(related_to_str, data, size);
    related_to_str[size] = '\0';

    // Create a icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_RELATEDTO_PROPERTY);
    if (prop == NULL) {
        free(related_to_str);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_relatedto(prop, related_to_str);

    // Additional operations to ensure code coverage
    const char *retrieved_str = icalproperty_get_relatedto(prop);
    if (retrieved_str != NULL) {
        // Perform operations with retrieved_str if necessary
    }

    // Clean up
    free(related_to_str);
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_530(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
