#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

extern "C" {
// Since icaltimezone.h is not available, we need to declare the function prototype
// for icaltimezone_set_system_zone_directory here if it's part of the C library.
void icaltimezone_set_system_zone_directory(const char *path);
}

extern "C" int LLVMFuzzerTestOneInput_557(const uint8_t *data, size_t size) {
    // Ensure the data size is not zero
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to simulate a directory path
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    close(fd);

    // Write the fuzz data to the temporary file
    FILE *file = fopen(tmpl, "wb");
    if (file != nullptr) {
        fwrite(data, 1, size, file);
        fclose(file);
    }

    // Call the function-under-test with the temporary file path
    icaltimezone_set_system_zone_directory(tmpl);

    // Clean up the temporary file
    unlink(tmpl);

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

    LLVMFuzzerTestOneInput_557(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
