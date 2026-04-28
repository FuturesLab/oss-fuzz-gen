#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Assuming the necessary function declaration for icaldurationtype_from_string
extern "C" {
    struct icaldurationtype {
        int is_neg;
        int weeks;
        int days;
        int hours;
        int minutes;
        int seconds;
    };

    struct icaldurationtype icaldurationtype_from_string(const char *str);
}

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
    // Ensure the input is null-terminated by copying it into a new buffer
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Handle memory allocation failure
    }
    
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Call the function-under-test
    struct icaldurationtype duration = icaldurationtype_from_string(null_terminated_data);

    // Free the allocated memory
    free(null_terminated_data);

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

    LLVMFuzzerTestOneInput_94(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
