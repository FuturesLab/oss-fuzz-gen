#include <libical/ical.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_849(const uint8_t *data, size_t size) {
    icalproperty *property = nullptr;
    char *ical_string = nullptr;

    if (size == 0) {
        return 0;
    }

    // Initialize libical
    icalerror_clear_errno();

    // Create a temporary buffer to hold the data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == nullptr) {
        return 0;
    }

    // Copy data into the buffer and ensure it is null-terminated
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Attempt to parse the buffer into an icalproperty
    property = icalproperty_new_from_string(buffer);

    // Free the temporary buffer
    free(buffer);

    if (property == nullptr) {
        return 0;
    }

    // Call the function-under-test
    ical_string = icalproperty_as_ical_string_r(property);

    // Free the icalproperty
    icalproperty_free(property);

    // Free the resulting string if it was allocated
    if (ical_string != nullptr) {
        free(ical_string);
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

    LLVMFuzzerTestOneInput_849(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
