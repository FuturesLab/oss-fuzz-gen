#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_205(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for extracting an icalvalue_kind
    if (size < sizeof(icalvalue_kind)) {
        return 0;
    }

    // Extract an icalvalue_kind from the input data
    icalvalue_kind value_kind = static_cast<icalvalue_kind>(data[0]);

    // Call the function-under-test
    icalproperty_kind property_kind = icalproperty_value_kind_to_kind(value_kind);

    // Use the result (property_kind) in some way to avoid compiler optimizations
    // that might remove the call to icalproperty_value_kind_to_kind
    (void)property_kind;

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

    LLVMFuzzerTestOneInput_205(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
