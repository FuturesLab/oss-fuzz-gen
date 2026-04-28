#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient for creating a string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *voter_string = (char *)malloc(size + 1);
    if (voter_string == NULL) {
        return 0;
    }
    memcpy(voter_string, data, size);
    voter_string[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_voter(voter_string, NULL);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    free(voter_string);

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

    LLVMFuzzerTestOneInput_37(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
