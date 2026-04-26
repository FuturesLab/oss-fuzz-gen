#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_197(const uint8_t *data, size_t size) {
    // Ensure there is at least one byte for the string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *voter = (char *)malloc(size + 1);
    if (voter == NULL) {
        return 0;
    }
    memcpy(voter, data, size);
    voter[size] = '\0';

    // Create an icalproperty object
    icalproperty *property = icalproperty_new(ICAL_VOTER_PROPERTY);
    if (property == NULL) {
        free(voter);
        return 0;
    }

    // Check if the voter string is valid before setting it
    if (strlen(voter) > 0) {
        // Call the function-under-test
        icalproperty_set_voter(property, voter);
    }

    // Cleanup
    icalproperty_free(property);
    free(voter);

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

    LLVMFuzzerTestOneInput_197(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
