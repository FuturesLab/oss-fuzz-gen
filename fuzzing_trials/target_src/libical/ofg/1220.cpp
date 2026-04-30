#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_1220(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 1) {
        return 0;
    }

    // Initialize an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_COMMENT_PROPERTY);

    // Use the input data to set some property values
    // Convert data to a null-terminated string
    char *str_data = (char *)malloc(size + 1);
    if (str_data == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(str_data, data, size);
    str_data[size] = '\0';

    // Set the string as a property value
    icalproperty_set_comment(prop, str_data);

    // Call the function-under-test
    // Here, we should invoke the function in a way that depends on the input data
    // Use the property in a way that exercises more code paths
    const char *comment = icalproperty_get_comment(prop);
    int result = 0;

    if (comment != NULL) {
        // Simulate some processing with the comment
        // For example, check its length or content
        size_t comment_length = strlen(comment);
        result = (comment_length > 0) ? 1 : 0;
    }

    // Clean up
    free(str_data);
    icalproperty_free(prop);

    return result;
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

    LLVMFuzzerTestOneInput_1220(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
