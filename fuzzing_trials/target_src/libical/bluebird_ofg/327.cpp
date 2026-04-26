#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // For close() and unlink()
#include <fcntl.h>   // For mkstemp()

extern "C" {
    #include "libical/ical.h"  // Include the correct header for libical
}

extern "C" int LLVMFuzzerTestOneInput_327(const uint8_t *data, size_t size) {
    // Check if size is non-zero to avoid unnecessary processing
    if (size == 0) return 0;

    // Create a temporary file to store the data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write data to the temporary file
    write(fd, data, size);
    close(fd);

    // Create an icalattach from the temporary file
    icalattach *attachment = icalattach_new_from_url(tmpl);

    // Call the function-under-test
    icalproperty *property = icalproperty_new_image(attachment);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    icalattach_unref(attachment);

    // Remove the temporary file
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

    LLVMFuzzerTestOneInput_327(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
