#include <stdint.h>
#include <stdlib.h>

// Function-under-test declaration
char * bam_aux2Z(const uint8_t *data);

int LLVMFuzzerTestOneInput_210(const uint8_t *data, size_t size) {
    // Ensure the data is non-null and has at least one byte
    if (data == NULL || size == 0) {
        return 0;
    }

    // Call the function-under-test
    char *result = bam_aux2Z(data);

    // If necessary, free the result if it's dynamically allocated
    // Assuming bam_aux2Z allocates memory that needs to be freed
    free(result);

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

    LLVMFuzzerTestOneInput_210(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
