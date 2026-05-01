#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

// Wrap the C headers and functions in extern "C" to ensure proper linkage
extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Prepare a null-terminated string from the input data
    char *uid = (char *)malloc(size + 1);
    if (uid == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(uid, data, size);
    uid[size] = '\0';

    // Call the function under test
    icalcomponent_set_uid(component, uid);

    // Clean up
    free(uid);
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_92(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
