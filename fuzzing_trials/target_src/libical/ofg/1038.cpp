#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for malloc and free
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1038(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icalrecurrencetype)) {
        return 0; // Exit if the input size is less than required for icalrecurrencetype
    }

    // Allocate memory for icalrecurrencetype
    struct icalrecurrencetype *recur = (struct icalrecurrencetype *)malloc(sizeof(struct icalrecurrencetype));
    if (recur == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Copy the input data into the icalrecurrencetype structure
    memcpy(recur, data, sizeof(struct icalrecurrencetype));

    // Call the function under test
    icalrecurrencetype_unref(recur);

    // Free the allocated memory
    free(recur);

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

    LLVMFuzzerTestOneInput_1038(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
