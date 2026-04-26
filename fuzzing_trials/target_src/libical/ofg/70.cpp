#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>

    // typedef struct icalpvl_elem_t* icalpvl_list;

    icalpvl_list icalpvl_newlist();
    void icalpvl_unshift(icalpvl_list list, void *data);
    void icalpvl_free(icalpvl_list list);
}

extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    // Create a icalpvl_list
    icalpvl_list list = icalpvl_newlist();

    // Ensure data is not NULL and has enough size
    if (size < sizeof(void*)) {
        return 0;
    }

    // Allocate memory for the data to be unshifted
    void *unshift_data = malloc(sizeof(void*));
    if (unshift_data == NULL) {
        return 0;
    }

    // Copy the fuzz data into the allocated memory
    memcpy(unshift_data, data, sizeof(void*));

    // Call the function-under-test
    icalpvl_unshift(list, unshift_data);

    // Clean up
    free(unshift_data);
    icalpvl_free(list);

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

    LLVMFuzzerTestOneInput_70(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
