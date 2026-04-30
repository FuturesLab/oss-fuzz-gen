#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_507(const uint8_t *data, size_t size) {
    // Initialize the icalproperty
    icalproperty *prop = icalproperty_new(ICAL_UID_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated for the string parameter
    char *uid = (char *)malloc(size + 1);
    if (uid == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(uid, data, size);
    uid[size] = '\0';

    // Call the function-under-test
    icalproperty_set_uid(prop, uid);

    // Additional operations to ensure code coverage
    const char *retrieved_uid = icalproperty_get_uid(prop);
    if (retrieved_uid != NULL) {
        // Perform a comparison or other operation to utilize the retrieved UID
        if (strcmp(uid, retrieved_uid) != 0) {
            // Handle unexpected case
        }
    }

    // Clean up
    icalproperty_free(prop);
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

    LLVMFuzzerTestOneInput_507(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
