#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_110(const uint8_t *data, size_t size) {
    struct bpf_object *obj = NULL;
    char *pathname = NULL;
    int fd;

    // Ensure size is sufficient for a pathname
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to use as a pathname
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    close(fd);

    // Allocate memory for the pathname and copy data into it
    pathname = (char *)malloc(size + 1);
    if (pathname == NULL) {
        unlink(tmpl);
        return 0;
    }
    memcpy(pathname, data, size);
    pathname[size] = '\0'; // Null-terminate the pathname

    // Call the function-under-test
    bpf_object__pin(obj, pathname);

    // Cleanup
    free(pathname);
    unlink(tmpl);

    return 0;
}