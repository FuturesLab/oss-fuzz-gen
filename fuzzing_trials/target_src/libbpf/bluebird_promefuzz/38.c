#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "/src/libbpf/include/uapi/linux/fcntl.h"
#include <unistd.h>
#include <sys/stat.h>
#include "/src/libbpf/include/linux/types.h"
#include "/src/libbpf/include/uapi/linux/perf_event.h"
#include "libbpf.h"

static void sample_cb(void *ctx, int cpu, void *data, __u32 size) {
    // Sample callback function for received data
}

static void lost_cb(void *ctx, int cpu, __u64 count) {
    // Lost callback function for lost records
}

static enum bpf_perf_event_ret event_cb(void *ctx, int cpu, struct perf_event_header *event) {
    // Event callback function for raw events
    return LIBBPF_PERF_EVENT_CONT;
}

int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    int map_fd = open("./dummy_file", O_CREAT | O_RDWR, 0644);
    if (map_fd < 0) {
        return 0;
    }

    // Initialize perf_buffer_opts and perf_buffer_raw_opts
    struct perf_buffer_opts pb_opts = {
        .sz = sizeof(struct perf_buffer_opts),
        .sample_period = 0
    };

    struct perf_buffer_raw_opts pb_raw_opts = {
        .sz = sizeof(struct perf_buffer_raw_opts),
        .cpu_cnt = 0,
        .cpus = NULL,
        .map_keys = NULL
    };

    struct perf_event_attr attr = {
        .type = PERF_TYPE_SOFTWARE,
        .size = sizeof(struct perf_event_attr),
        .config = PERF_COUNT_SW_CPU_CLOCK,
        .sample_period = 0,
        .sample_type = 0,
        .read_format = 0
    };

    // Create perf_buffer using perf_buffer__new
    struct perf_buffer *pb = perf_buffer__new(map_fd, 1, sample_cb, lost_cb, NULL, &pb_opts);
    if (pb) {
        size_t buf_cnt = perf_buffer__buffer_cnt(pb);
        for (size_t i = 0; i < buf_cnt; i++) {
            int fd = perf_buffer__buffer_fd(pb, i);
            if (fd >= 0) {
                perf_buffer__consume_buffer(pb, i);
            }
        }
        perf_buffer__free(pb);
    }

    // Create raw perf_buffer using perf_buffer__new_raw
    struct perf_buffer *pb_raw = perf_buffer__new_raw(map_fd, 1, &attr, event_cb, NULL, &pb_raw_opts);
    if (pb_raw) {
        size_t buf_cnt = perf_buffer__buffer_cnt(pb_raw);
        for (size_t i = 0; i < buf_cnt; i++) {
            void *buf;
            size_t buf_size;
            if (perf_buffer__buffer(pb_raw, i, &buf, &buf_size) == 0) {
                // Successfully retrieved buffer
            }
        }
        perf_buffer__free(pb_raw);
    }

    close(map_fd);
    unlink("./dummy_file");
    return 0;
}