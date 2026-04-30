#include <stdint.h>
#include <stddef.h>

extern "C" {
#include <libical/ical.h> // Assuming the correct path for libical headers
}

extern "C" {

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    if (size < 2) return 0; // Ensure there is at least 2 bytes to read

    // Initialize an icalproperty object with a specific property kind
    icalproperty *prop = icalproperty_new(ICAL_SUMMARY_PROPERTY);

    // Cast the first byte of data to icalproperty_querylevel
    icalproperty_querylevel query_level = 
        static_cast<icalproperty_querylevel>(data[0]);

    // Use the second byte of data to create a string for the property value
    char value[2] = { static_cast<char>(data[1]), '\0' };
    icalproperty_set_summary(prop, value);

    // Call the function-under-test
    icalproperty_set_querylevel(prop, query_level);

    // Clean up
    icalproperty_free(prop);

    return 0;
}

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

    LLVMFuzzerTestOneInput_54(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
