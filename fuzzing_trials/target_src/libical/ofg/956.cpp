#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_956(const uint8_t *data, size_t size) {
    // Ensure there's enough data for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_URL_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Allocate memory for the URL string and ensure it's null-terminated
    char *url = (char *)malloc(size + 1);
    if (url == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(url, data, size);
    url[size] = '\0';

    // Call the function-under-test
    icalproperty_set_url(prop, url);

    // Clean up
    free(url);
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_956(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
