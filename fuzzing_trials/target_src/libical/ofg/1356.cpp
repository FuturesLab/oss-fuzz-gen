#include <stdint.h>
#include <stdlib.h>
#include <libical/ical.h>
#include <string.h> // Include the necessary header for memcpy

extern "C" {
    void icalrecurrencetype_ref(struct icalrecurrencetype *);
}

extern "C" int LLVMFuzzerTestOneInput_1356(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icalrecurrencetype)) {
        return 0; // Not enough data to fill icalrecurrencetype
    }

    // Allocate memory for icalrecurrencetype
    struct icalrecurrencetype recur;
    
    // Copy data into the structure, ensuring we don't overflow
    memcpy(&recur, data, sizeof(struct icalrecurrencetype));

    // Call the function-under-test
    icalrecurrencetype_ref(&recur);

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

    LLVMFuzzerTestOneInput_1356(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
