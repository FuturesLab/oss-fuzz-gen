#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1012(const uint8_t *data, size_t size) {
    // Initialize a icalproperty object
    icalproperty *property = icalproperty_new(ICAL_ATTACH_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated before using it as a string
    char *data_str = (char *)malloc(size + 1);
    if (data_str == NULL) {
        icalproperty_free(property);
        return 0;
    }
    memcpy(data_str, data, size);
    data_str[size] = '\0';

    // Set the string as the value for the property
    icalattach *attachment = icalattach_new_from_data(data_str, NULL, NULL);
    if (attachment != NULL) {
        icalproperty_set_attach(property, attachment);

        // Retrieve and work with the attachment
        icalattach *retrieved_attachment = icalproperty_get_attach(property);
        if (retrieved_attachment != NULL) {
            // Perform operations on the retrieved attachment to increase code coverage
            const unsigned char *retrieved_data = (const unsigned char *)icalattach_get_data(retrieved_attachment);
            if (retrieved_data != NULL) {
                // Simulate some processing on the retrieved data
                size_t retrieved_size = strlen((const char *)retrieved_data);
                if (retrieved_size > 0) {
                    // Example processing: check the first character
                    char first_char = retrieved_data[0];
                    (void)first_char; // Use the character to avoid unused variable warning
                }

                // Additional operations to increase code coverage
                icalproperty_set_comment(property, "Test comment");
                const char *comment = icalproperty_get_comment(property);
                if (comment != NULL) {
                    // Use the comment to avoid unused variable warning
                    (void)comment;
                }

                // Further operations to explore more code paths
                icalattach_ref(retrieved_attachment);
                icalattach_unref(retrieved_attachment);

                // Additional property manipulations to increase coverage
                icalproperty_set_description(property, "Test description");
                const char *description = icalproperty_get_description(property);
                if (description != NULL) {
                    (void)description;
                }

                icalproperty_set_summary(property, "Test summary");
                const char *summary = icalproperty_get_summary(property);
                if (summary != NULL) {
                    (void)summary;
                }
            }
            icalattach_unref(retrieved_attachment);
        }
    }

    // Clean up
    icalproperty_free(property);
    free(data_str);

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

    LLVMFuzzerTestOneInput_1012(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
