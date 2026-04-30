#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_568(const uint8_t *data, size_t size) {
    // Ensure that the input data is sufficient to create a valid icalvalue
    if (size < 1) return 0;

    // Create a string from the input data
    char *input_data = (char *) malloc(size + 1);
    if (input_data == NULL) return 0;
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Determine the kind of icalvalue to create
    // For fuzzing, we can use a simple heuristic: use the first byte to determine the kind
    icalvalue_kind kind = static_cast<icalvalue_kind>(data[0] % ICAL_NO_VALUE);

    // Create an icalvalue from the input data
    icalvalue *value = icalvalue_new_from_string(kind, input_data);
    free(input_data);

    // Ensure the icalvalue is valid
    if (value == NULL) return 0;

    // Call the function-under-test
    char *ical_string = icalvalue_as_ical_string_r(value);

    // Clean up
    if (ical_string != NULL) {
        free(ical_string);
    }
    icalvalue_free(value);

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

    LLVMFuzzerTestOneInput_568(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
