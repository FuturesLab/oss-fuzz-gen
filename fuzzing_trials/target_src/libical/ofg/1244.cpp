#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/icalerror.h> // Include necessary header for icalerror_restore and icalerrorstate

    // Function-under-test
    void icalerror_restore(const char *error, icalerrorstate state);
}

extern "C" int LLVMFuzzerTestOneInput_1244(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a non-null string and a valid icalerrorstate
    if (size < 2) {
        return 0;
    }

    // Extract a non-null string from the input data
    char error[2];
    error[0] = (char)data[0];
    error[1] = '\0';  // Null-terminate the string

    // Extract a valid icalerrorstate from the input data
    icalerrorstate state = (icalerrorstate)(data[1] % 3); // Assuming 3 possible states

    // Call the function-under-test
    icalerror_restore(error, state);

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

    LLVMFuzzerTestOneInput_1244(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
