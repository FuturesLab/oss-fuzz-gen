#include <stdint.h>
#include <stddef.h>

// Assuming the necessary library header for icalproperty_participanttype
extern "C" {
    // Define the icalproperty_participanttype enum if not defined in a header
    typedef enum icalproperty_participanttype {
        ICAL_PARTICIPANTTYPE_UNKNOWN,
        ICAL_PARTICIPANTTYPE_REQUIRED,
        ICAL_PARTICIPANTTYPE_OPTIONAL,
        ICAL_PARTICIPANTTYPE_RESOURCE,
        ICAL_PARTICIPANTTYPE_NON_PARTICIPANT
    } icalproperty_participanttype;

    // Include the function-under-test from the library
    const char * icalproperty_participanttype_to_string(icalproperty_participanttype);
}

extern "C" int LLVMFuzzerTestOneInput_551(const uint8_t *data, size_t size) {
    // Define and initialize the variable for icalproperty_participanttype
    icalproperty_participanttype participant_type;

    // Check the size to ensure it can fit into the enum type
    if (size < sizeof(icalproperty_participanttype)) {
        return 0;
    }

    // Cast data to icalproperty_participanttype
    participant_type = static_cast<icalproperty_participanttype>(data[0] % 5); // Ensure the value is within enum range

    // Call the function-under-test
    const char *result = icalproperty_participanttype_to_string(participant_type);

    // Optionally, use the result to prevent compiler optimizations from removing the call
    if (result) {
        volatile char dummy = result[0];
        (void)dummy;
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

    LLVMFuzzerTestOneInput_551(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
