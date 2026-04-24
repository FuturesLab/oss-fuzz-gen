#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Assuming the function is declared in a header file
// #include "sam.h"

// Mock implementation of the function-under-test for demonstration purposes
int sam_index_build3_26(const char *arg1, const char *arg2, int arg3, int arg4) {
    // Function logic here
    return 0; // Placeholder return
}

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to create two filenames
    }

    // Create temporary files for the first two string arguments
    char tmpl1[] = "/tmp/fuzzfile1XXXXXX";
    char tmpl2[] = "/tmp/fuzzfile2XXXXXX";
    int fd1 = mkstemp(tmpl1);
    int fd2 = mkstemp(tmpl2);

    if (fd1 == -1 || fd2 == -1) {
        if (fd1 != -1) close(fd1);
        if (fd2 != -1) close(fd2);
        return 0;
    }

    // Write data to the first temporary file
    write(fd1, data, size / 2);
    close(fd1);

    // Write data to the second temporary file
    write(fd2, data + size / 2, size - size / 2);
    close(fd2);

    // Use some fixed values for the integer arguments
    int arg3 = 1;
    int arg4 = 2;

    // Call the function-under-test
    sam_index_build3_26(tmpl1, tmpl2, arg3, arg4);

    // Clean up temporary files
    unlink(tmpl1);
    unlink(tmpl2);

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

    LLVMFuzzerTestOneInput_26(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
