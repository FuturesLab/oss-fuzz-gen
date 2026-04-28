#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a non-null string
    if (size == 0) {
        return 0;  // Exit early if there's no data to process
    }

    // Allocate memory for the description string and copy data to it
    char *description = new char[size + 1];
    memcpy(description, data, size);
    description[size] = '\0';  // Null-terminate the string

    // Create a new icalproperty object with a more meaningful property type
    icalproperty *prop = icalproperty_new(ICAL_SUMMARY_PROPERTY);

    // Call the function-under-test
    icalproperty_set_styleddescription(prop, description);

    // Clean up
    icalproperty_free(prop);
    delete[] description;

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

    LLVMFuzzerTestOneInput_118(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
