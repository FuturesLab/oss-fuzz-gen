#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_666(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the string and ensure it's null-terminated
    char *str = (char *)malloc(size + 1);
    if (!str) {
        return 0;
    }
    memcpy(str, data, size);
    str[size] = '\0';

    // Call the function-under-test with some additional logic to ensure meaningful input
    // Assuming icalproperty_vanew_recurexpand expects a valid iCalendar string,
    // we can prepend a valid property name to increase the chance of valid input.
    const char *prefix = "RRULE:";
    size_t prefix_len = strlen(prefix);

    char *full_str = (char *)malloc(prefix_len + size + 1);
    if (!full_str) {
        free(str);
        return 0;
    }
    memcpy(full_str, prefix, prefix_len);
    memcpy(full_str + prefix_len, str, size);
    full_str[prefix_len + size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_recurexpand(full_str, nullptr);

    // Clean up
    if (prop != nullptr) {
        icalproperty_free(prop);
    }
    free(str);
    free(full_str);

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

    LLVMFuzzerTestOneInput_666(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
