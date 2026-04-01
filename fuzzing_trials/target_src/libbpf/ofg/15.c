#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    struct bpf_object *obj = NULL;
    int result;

    // Create a temporary file to store the BPF object data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Load the BPF object from the file
    obj = bpf_object__open(tmpl);
    if (obj != NULL) {
        // Call the function-under-test
        result = bpf_object__load(obj);

        // Clean up
        bpf_object__close(obj);
    }

    // Remove the temporary file
    close(fd);
    unlink(tmpl);

    return 0;
}