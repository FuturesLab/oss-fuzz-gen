#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/icalproperty.h>
}

extern "C" int LLVMFuzzerTestOneInput_839(const uint8_t *data, size_t size) {
    // Ensure that the data is null-terminated to be used as a C string
    if (size == 0) {
        return 0; // No data to process
    }

    char *tzname = (char *)malloc(size + 1);
    if (tzname == NULL) {
        return 0; // Memory allocation failed
    }
    
    memcpy(tzname, data, size);
    tzname[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_tzname(tzname);

    // Check if the property was created successfully
    if (prop != NULL) {
        // Perform operations on the property to increase code coverage
        icalproperty_kind kind = icalproperty_isa(prop);
        if (kind == ICAL_TZNAME_PROPERTY) {
            // Further processing can be done here if needed
        }
        icalproperty_free(prop);
    }

    free(tzname);

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

    LLVMFuzzerTestOneInput_839(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
