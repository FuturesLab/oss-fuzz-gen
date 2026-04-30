#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_612(const uint8_t *data, size_t size) {
    // Ensure data is null-terminated for string operations
    char *uid = (char *)malloc(size + 1);
    if (uid == NULL) {
        return 0; // Handle allocation failure
    }
    memcpy(uid, data, size);
    uid[size] = '\0'; // Null-terminate the string

    // Create a new icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        free(uid);
        return 0; // Handle allocation failure
    }

    // Call the function-under-test
    icalcomponent_set_uid(component, uid);

    // Clean up
    icalcomponent_free(component);
    free(uid);

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

    LLVMFuzzerTestOneInput_612(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
