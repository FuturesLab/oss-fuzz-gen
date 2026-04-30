#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_537(const uint8_t *data, size_t size) {
    // Initialize the icalproperty object with a specific property type
    icalproperty *property = icalproperty_new(ICAL_COMMENT_PROPERTY);
    
    // Ensure the property is not NULL
    if (property == NULL) {
        return 0;
    }

    // Use the input data to set a property value if size is sufficient
    if (size > 0) {
        // Convert data to a string and set it as a value of the property
        char *value = (char *)malloc(size + 1);
        if (value != NULL) {
            memcpy(value, data, size);
            value[size] = '\0';  // Null-terminate the string

            icalproperty_set_comment(property, value);
            free(value);
        }
    }

    // Call the function-under-test
    const char *ical_string = icalproperty_as_ical_string(property);

    // Check if the conversion to string was successful
    if (ical_string != NULL) {
        // Print the string to ensure it is being processed
        printf("%s\n", ical_string);
    }

    // Clean up
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_537(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
