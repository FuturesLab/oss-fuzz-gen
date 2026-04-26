#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_401(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the string and copy data into it
    char *xlicclustercount = (char *)malloc(size + 1);
    if (xlicclustercount == NULL) {
        return 0;
    }
    memcpy(xlicclustercount, data, size);
    xlicclustercount[size] = '\0';  // Null-terminate the string

    // Create a new icalproperty object with a valid property kind
    icalproperty *prop = icalproperty_new(ICAL_XLICCLUSTERCOUNT_PROPERTY);
    if (prop == NULL) {
        free(xlicclustercount);
        return 0;
    }

    // Call the function under test
    icalproperty_set_xlicclustercount(prop, xlicclustercount);

    // Validate that the property has been set correctly
    const char *retrieved_value = icalproperty_get_xlicclustercount(prop);
    if (retrieved_value != NULL && strcmp(retrieved_value, xlicclustercount) != 0) {
        // If the set value and retrieved value don't match, there is an issue
        icalproperty_free(prop);
        free(xlicclustercount);
        return 0;
    }

    // Clean up
    icalproperty_free(prop);
    free(xlicclustercount);

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

    LLVMFuzzerTestOneInput_401(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
