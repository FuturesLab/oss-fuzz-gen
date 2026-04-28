#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "libical/ical.h"

    // Assuming the function is part of the libical library
    icalpvl_elem_t* icalpvl_new_element(void*, icalpvl_elem_t*, icalpvl_elem_t*);
}

extern "C" int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create meaningful inputs
    if (size < 3) {
        return 0;
    }

    // Initialize the parameters for icalpvl_new_element
    void *param1 = (void *)(data); // Use data pointer as a dummy non-NULL pointer
    icalpvl_elem_t* param2 = (icalpvl_elem_t*)(data + 1); // Use pointer arithmetic to get a non-NULL pointer
    icalpvl_elem_t* param3 = (icalpvl_elem_t*)(data + 2); // Use pointer arithmetic to get a non-NULL pointer

    // Call the function-under-test
    icalpvl_elem_t* result = icalpvl_new_element(param1, param2, param3);

    // Optionally, perform some checks or operations on the result
    // ...

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

    LLVMFuzzerTestOneInput_105(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
