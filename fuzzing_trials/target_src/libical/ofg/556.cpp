#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

extern "C" {
    // Assuming that icaltimezone_set_system_zone_directory is a function 
    // from the C project that needs to be declared here.
    void icaltimezone_set_system_zone_directory(const char *path);
}

extern "C" int LLVMFuzzerTestOneInput_556(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a directory path
    char tmpl[] = "/tmp/fuzzdirXXXXXX";
    int fd = mkstemp(tmpl);

    // Close the file descriptor as we only need the path
    if (fd != -1) {
        close(fd);
    }

    // Ensure the provided data is not empty
    if (size > 0) {
        // Copy the fuzz data into the temporary file path
        // Ensure it is null-terminated
        size_t copy_size = size < sizeof(tmpl) - 1 ? size : sizeof(tmpl) - 1;
        memcpy(tmpl, data, copy_size);
        tmpl[copy_size] = '\0';

        // Call the function-under-test with the temporary file path
        icaltimezone_set_system_zone_directory(tmpl);
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

    LLVMFuzzerTestOneInput_556(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
