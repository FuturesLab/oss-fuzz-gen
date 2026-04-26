#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_936(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the string and ensure it is null-terminated
    char *restriction_string = (char *)malloc(size + 1);
    if (restriction_string == NULL) {
        return 0;
    }
    memcpy(restriction_string, data, size);
    restriction_string[size] = '\0';

    // Check if the restriction_string is non-empty to increase the chance of meaningful input
    if (strlen(restriction_string) > 0) {
        // Call the function-under-test
        icalproperty *property = icalproperty_vanew_restriction(restriction_string, NULL);

        // Clean up
        if (property != NULL) {
            icalproperty_free(property);
        }
    }

    free(restriction_string);

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

    LLVMFuzzerTestOneInput_936(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
