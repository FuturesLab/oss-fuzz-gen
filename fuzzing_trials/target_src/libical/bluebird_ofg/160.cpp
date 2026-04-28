#include <string.h>
#include <sys/stat.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib> // Include for malloc and free

extern "C" {
#include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Ensure the data is null-terminated to safely use it as a string
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Create an icalattach object from the input data
    // We need to provide a valid free function or NULL if we don't need custom free logic
    icalattach *attachment = icalattach_new_from_data(null_terminated_data, (icalattach_free_fn_t)free, NULL);

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_image(attachment, NULL);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    if (attachment != NULL) {
        icalattach_unref(attachment);
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

    LLVMFuzzerTestOneInput_160(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
