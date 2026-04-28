#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *comment = (char *)malloc(size + 1);
    if (comment == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(comment, data, size);
    comment[size] = '\0';

    // Ensure the comment is not empty
    if (strlen(comment) == 0) {
        free(comment);
        icalcomponent_free(component);
        return 0;
    }

    // Call the function under test
    icalcomponent_set_comment(component, comment);

    // Additional operations to increase code coverage
    // For example, retrieve the comment and check it
    const char *retrieved_comment = icalcomponent_get_comment(component);
    if (retrieved_comment != NULL) {
        // Do something with retrieved_comment if needed
    }

    // Clean up
    free(comment);
    icalcomponent_free(component);

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

    LLVMFuzzerTestOneInput_54(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
