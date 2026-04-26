#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for strlen

extern "C" {
    #include "libical/ical.h"  // Correct path for libical headers
}

extern "C" int LLVMFuzzerTestOneInput_506(const uint8_t *data, size_t size) {
    // Initialize a variable of type icalproperty_participanttype
    icalproperty_participanttype participant_type;

    // Ensure the data size is sufficient to map to the enum
    if (size < sizeof(int)) {
        return 0;
    }

    // Map the input data to the enum type
    participant_type = static_cast<icalproperty_participanttype>(data[0] % ICAL_PARTICIPANTTYPE_X);

    // Call the function-under-test
    const char *result = icalproperty_participanttype_to_string(participant_type);

    // Use the result in some way to avoid compiler optimizations
    if (result != nullptr) {
        // Do something trivial with the result
        volatile size_t length = strlen(result);
        (void)length;
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

    LLVMFuzzerTestOneInput_506(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
