#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h> // Correct header path for icalcomponent
}

extern "C" int LLVMFuzzerTestOneInput_613(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0; // Return immediately if size is zero
    }

    // Initialize an icalcomponent object
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0; // Return if component creation fails
    }

    // Ensure the data is null-terminated before using it as a string
    char *uid = (char *)malloc(size + 1);
    if (uid == NULL) {
        icalcomponent_free(component);
        return 0; // Return if memory allocation fails
    }
    memcpy(uid, data, size);
    uid[size] = '\0';

    // Ensure the UID is valid and non-empty
    if (strlen(uid) > 0) {
        // Call the function-under-test
        icalcomponent_set_uid(component, uid);
    }

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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_613(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
