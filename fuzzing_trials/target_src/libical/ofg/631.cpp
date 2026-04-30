#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>  // For close and unlink

extern "C" {
    #include <libical/icaltimezone.h> // Adjusted include for icaltimezone functions

    // Fuzzing harness for icaltimezone_dump_changes
    int LLVMFuzzerTestOneInput_631(const uint8_t *data, size_t size) {
        // Ensure there's enough data to create a meaningful timezone
        if (size < 1) {
            return 0;
        }

        // Create a dummy icaltimezone object
        icaltimezone *timezone = icaltimezone_new();

        // Ensure the timezone is not NULL
        if (timezone == NULL) {
            return 0;
        }

        // Convert the first byte of data to an integer for the second parameter
        int changes = static_cast<int>(data[0]);

        // Create a temporary file to pass as the FILE* parameter
        char tmpl[] = "/tmp/fuzzfileXXXXXX";
        int fd = mkstemp(tmpl);
        if (fd == -1) {
            icaltimezone_free(timezone, 1); // Free the timezone object
            return 0;
        }

        FILE *file = fdopen(fd, "w+");
        if (file == NULL) {
            close(fd);
            icaltimezone_free(timezone, 1); // Free the timezone object
            return 0;
        }

        // Call the function-under-test
        icaltimezone_dump_changes(timezone, changes, file);

        // Clean up
        fclose(file);
        unlink(tmpl);
        icaltimezone_free(timezone, 1); // Free the timezone object

        return 0;
    }
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

    LLVMFuzzerTestOneInput_631(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
