#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_663(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated
    if (size == 0) {
        return 0; // Exit if the input size is zero
    }

    char *locale_str = (char *)malloc(size + 1);
    if (locale_str == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(locale_str, data, size);
    locale_str[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_defaultlocale(locale_str);

    // Attempt to utilize the property to ensure code coverage
    if (prop != NULL) {
        icalproperty_kind kind = icalproperty_isa(prop);
        
        // Additional operations to increase code coverage
        icalproperty_set_comment(prop, locale_str);
        const char *comment = icalproperty_get_comment(prop);
        if (comment != NULL) {
            // Perform a simple check to ensure the comment was set
            if (strcmp(comment, locale_str) == 0) {
                // Successfully set and retrieved the comment
            }
        }

        icalproperty_free(prop);
    }

    free(locale_str);

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

    LLVMFuzzerTestOneInput_663(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
