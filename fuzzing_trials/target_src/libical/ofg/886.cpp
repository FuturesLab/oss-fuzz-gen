#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for malloc and free
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_886(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a new icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_PRODID_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Create a string from the input data
    char *inputStr = (char *)malloc(size + 1);
    if (inputStr == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(inputStr, data, size);
    inputStr[size] = '\0';

    // Set the prodid property using the input string
    icalproperty_set_prodid(prop, inputStr);

    // Call the function-under-test
    const char *prodid = icalproperty_get_prodid(prop);

    // Check if the prodid is not null and has some content
    if (prodid && prodid[0] != '\0') {
        // Further process or log the prodid to ensure coverage
        // For example, print it or pass it to another function
        // This is just a placeholder to ensure that the prodid is used
        // printf("Prodid: %s\n", prodid);
    }

    // Clean up
    free(inputStr);
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

    LLVMFuzzerTestOneInput_886(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
