#include <stdint.h>
#include <stddef.h>
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/icalproperty.h> // Correct header for icalproperty_string_to_status
}

extern "C" int LLVMFuzzerTestOneInput_645(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated before passing it as a string
    if (size == 0) {
        return 0;
    }

    // Create a buffer with an extra byte for the null-terminator
    char *null_terminated_data = new char[size + 1];
    if (null_terminated_data == NULL) {
        return 0;
    }

    // Copy the input data into the buffer and null-terminate it
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Call the function-under-test
    icalproperty_status status = icalproperty_string_to_status(null_terminated_data);

    // Clean up
    delete[] null_terminated_data;

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

    LLVMFuzzerTestOneInput_645(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
