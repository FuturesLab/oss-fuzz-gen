#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_209(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create a valid string
    if (size == 0) return 0;

    // Allocate memory for the property string and ensure it's null-terminated
    char *propertyString = static_cast<char *>(malloc(size + 1));
    if (propertyString == nullptr) return 0;
    memcpy(propertyString, data, size);
    propertyString[size] = '\0';

    // Create an icalproperty from the string
    icalproperty *prop = icalproperty_new_from_string(propertyString);
    free(propertyString);

    if (prop != nullptr) {
        // Call the function-under-test
        struct icaltimetype recurrenceId = icalproperty_get_recurrenceid(prop);

        // Free the icalproperty
        icalproperty_free(prop);
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

    LLVMFuzzerTestOneInput_209(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
