#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    // Forward declaration of the function-under-test
    icalproperty *icalproperty_vanew_querylevel(icalproperty_querylevel, ...);
}

extern "C" int LLVMFuzzerTestOneInput_1366(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a value for the enumeration
    if (size < sizeof(icalproperty_querylevel) + 1) {
        return 0;
    }

    // Extract an enumeration value from the input data
    icalproperty_querylevel querylevel = static_cast<icalproperty_querylevel>(data[0] % (ICAL_QUERYLEVEL_NONE + 1));

    // Prepare a non-null string to use as a variadic argument
    const char *non_null_string = reinterpret_cast<const char*>(&data[1]);

    // Call the function-under-test with the non-null string
    icalproperty *property = icalproperty_vanew_querylevel(querylevel, non_null_string, NULL);

    // Clean up the created property if not NULL
    if (property != NULL) {
        icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_1366(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
