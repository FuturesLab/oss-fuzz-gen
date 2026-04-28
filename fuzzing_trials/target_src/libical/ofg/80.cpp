#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/icalproperty.h>
}

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to be used as a string
    char *voter_data = (char *)malloc(size + 1);
    if (voter_data == NULL) {
        return 0; // Exit if memory allocation fails
    }

    memcpy(voter_data, data, size);
    voter_data[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalproperty *property = icalproperty_new_voter(voter_data);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    free(voter_data);

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

    LLVMFuzzerTestOneInput_80(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
