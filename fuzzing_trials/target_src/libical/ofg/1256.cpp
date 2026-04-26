#include <stdint.h>
#include <stddef.h>
#include <string.h> // For memcpy

extern "C" {
    #include <libical/ical.h> // Correct header for libical functions
}

extern "C" int LLVMFuzzerTestOneInput_1256(const uint8_t *data, size_t size) {
    // Initialize an icalproperty object with a specific property kind
    icalproperty *prop = icalproperty_new(ICAL_RECURRENCEID_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Initialize an icaltimetype object
    struct icaltimetype recurrence_id;
    
    // Ensure size is sufficient to populate icaltimetype
    if (size >= sizeof(struct icaltimetype)) {
        // Copy data into recurrence_id, ensuring no overflow
        memcpy(&recurrence_id, data, sizeof(struct icaltimetype));
    } else {
        // If not enough data, set default values
        recurrence_id = icaltime_null_time();
    }

    // Call the function-under-test
    icalproperty_set_recurrenceid(prop, recurrence_id);

    // Additional function calls to increase code coverage
    icalproperty_kind kind = icalproperty_isa(prop);
    if (kind != ICAL_NO_PROPERTY) {
        const char* prop_name = icalproperty_kind_to_string(kind);
        if (prop_name) {
            // Use the property name in some way to ensure it is accessed
            (void)prop_name;
        }
    }

    // Free the icalproperty object
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

    LLVMFuzzerTestOneInput_1256(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
