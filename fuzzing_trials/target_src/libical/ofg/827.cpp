#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_827(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the input data and ensure it's null-terminated
    char *inputData = (char *)malloc(size + 1);
    if (inputData == nullptr) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Create an icalvalue from the input data
    // Assuming we need to determine the kind of icalvalue
    icalvalue_kind kind = ICAL_ANY_VALUE; // or another appropriate kind
    icalvalue *value = icalvalue_new_from_string(kind, inputData);

    // Free the input data memory
    free(inputData);

    // If the value is successfully created, convert it to an iCal string
    if (value != nullptr) {
        const char *icalString = icalvalue_as_ical_string(value);
        // Optionally, you could do something with icalString here

        // Free the icalvalue
        icalvalue_free(value);
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

    LLVMFuzzerTestOneInput_827(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
