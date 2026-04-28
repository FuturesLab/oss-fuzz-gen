#include <libical/ical.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include for write, close
#include <stdio.h>   // Include for remove

extern "C" int LLVMFuzzerTestOneInput_1134(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid icalattach
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to simulate an attachment
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Create an icalattach from the file
    icalattach *attachment = icalattach_new_from_url(tmpl);
    if (attachment == NULL) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    icalproperty *property = icalproperty_new_image(attachment);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    icalattach_unref(attachment);
    remove(tmpl);

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

    LLVMFuzzerTestOneInput_1134(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
