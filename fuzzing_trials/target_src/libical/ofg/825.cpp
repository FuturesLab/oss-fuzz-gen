#include <stdint.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_825(const uint8_t *data, size_t size) {
    // Call the function-under-test
    struct icalrecurrencetype *recurrence = icalrecurrencetype_new();

    // Check if the function returned a non-NULL pointer
    if (recurrence != NULL) {
        // Perform some operations on the recurrence object if needed
        // For now, we will just free it to avoid memory leaks
        free(recurrence);
    }

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

    LLVMFuzzerTestOneInput_825(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
