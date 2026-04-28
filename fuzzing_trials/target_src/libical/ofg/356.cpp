#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    // Include the necessary C headers for the project-under-test
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_356(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *xlicmimecid = (char *)malloc(size + 1);
    if (xlicmimecid == NULL) {
        return 0;
    }

    // Copy the data into the string and null-terminate it
    memcpy(xlicmimecid, data, size);
    xlicmimecid[size] = '\0';

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_XLICERROR_PROPERTY);
    if (prop == NULL) {
        free(xlicmimecid);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_xlicmimecid(prop, xlicmimecid);

    // Clean up
    icalproperty_free(prop);
    free(xlicmimecid);

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

    LLVMFuzzerTestOneInput_356(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
