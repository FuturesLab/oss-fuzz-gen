#include <libical/ical.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_605(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an enumeration value
    if (size < sizeof(icalproperty_participanttype)) {
        return 0;
    }

    // Extract an enumeration value from the input data
    icalproperty_participanttype participant_type = static_cast<icalproperty_participanttype>(data[0] % ICAL_PARTICIPANTTYPE_X);

    // Call the function-under-test
    icalproperty *property = icalproperty_new_participanttype(participant_type);

    // Clean up
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

    LLVMFuzzerTestOneInput_605(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
