#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "/src/libbpf/include/uapi/linux/fcntl.h"
#include "libbpf.h"

int LLVMFuzzerTestOneInput_433(const uint8_t *data, size_t size) {
    struct bpf_object *obj = NULL;
    int result;

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }

    // Load the BPF object from the temporary file
    obj = bpf_object__open(tmpl);
    if (!obj) {
        close(fd);
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__load with bpf_object__prepare

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__prepare with bpf_object__load
    result = bpf_object__load(obj);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__load to libbpf_strerror
    int ret_bpf_program__fd_hunbg = bpf_program__fd(NULL);
    if (ret_bpf_program__fd_hunbg < 0){
    	return 0;
    }

    int ret_libbpf_strerror_cttde = libbpf_strerror(ret_bpf_program__fd_hunbg, (char *)"r", (size_t )result);
    if (ret_libbpf_strerror_cttde < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);
    close(fd);
    unlink(tmpl);

    return 0;
}