#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    // Ensure that we have enough data to extract a valid enumeration value
    if (size < 1) {
        return 0;
    }

    // Convert the input data to an icalproperty_transp value
    icalproperty_transp transp_value = static_cast<icalproperty_transp>(data[0] % 3);

    // Create a dummy string from the remaining data to pass as an argument
    const char *dummy_string = nullptr;
    if (size > 1) {
        dummy_string = reinterpret_cast<const char*>(data + 1);
    }

    // Call the function-under-test with the dummy string
    icalproperty *prop = icalproperty_vanew_transp(transp_value, dummy_string, NULL);

    // Clean up if necessary
    if (prop != NULL) {
        icalproperty_free(prop);
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

    LLVMFuzzerTestOneInput_76(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
