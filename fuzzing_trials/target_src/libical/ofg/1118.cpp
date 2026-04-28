#include <libical/ical.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_1118(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated
    if (size == 0) {
        return 0; // Exit early if there is no data
    }
    
    char *url = (char *)malloc(size + 1);
    if (url == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(url, data, size);
    url[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_replyurl(url);

    // Check if the property is created to ensure the function is being tested
    if (prop != NULL) {
        // Access some property fields to increase code coverage
        icalproperty_kind kind = icalproperty_isa(prop);
        if (kind != ICAL_NO_PROPERTY) {
            // Perform additional operations if needed
        }
        icalproperty_free(prop);
    }
    
    free(url);

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

    LLVMFuzzerTestOneInput_1118(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
