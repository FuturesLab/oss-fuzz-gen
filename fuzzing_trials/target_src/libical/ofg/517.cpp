#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_517(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to be meaningful
    if (size < 1) {
        return 0;
    }

    // Initialize an icalproperty object with a specific property type
    icalproperty *property = icalproperty_new(ICAL_COMMENT_PROPERTY);

    // Check if the property was created successfully
    if (property == NULL) {
        return 0;
    }

    // Use the input data to set a comment, ensuring it's null-terminated
    char *comment = (char *)malloc(size + 1);
    if (comment == NULL) {
        icalproperty_free(property);
        return 0;
    }
    memcpy(comment, data, size);
    comment[size] = '\0';

    // Set the comment to the property
    icalproperty_set_comment(property, comment);

    // Call the function-under-test
    const char *retrieved_comment = icalproperty_get_comment(property);

    // Use the retrieved comment in some way to avoid compiler optimizations removing the call
    // Add more meaningful checks to increase code coverage
    if (retrieved_comment != NULL && strcmp(retrieved_comment, comment) == 0) {
        // Do something trivial if the comment matches
        icalproperty_set_comment(property, "Comment matches");
    } else {
        // Handle the case where the comment does not match
        icalproperty_set_comment(property, "Comment does not match");
    }

    // Further use of the property to ensure more code paths are covered
    icalproperty_kind kind = icalproperty_isa(property);
    if (kind == ICAL_COMMENT_PROPERTY) {
        // Perform some operation if the kind matches
        icalproperty_set_comment(property, "Property kind matches");
    } else {
        // Handle other kinds
        icalproperty_set_comment(property, "Property kind does not match");
    }

    // Clean up
    free(comment);
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

    LLVMFuzzerTestOneInput_517(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
