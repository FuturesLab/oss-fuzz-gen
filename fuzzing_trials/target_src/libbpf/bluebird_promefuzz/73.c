#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "libbpf.h"
#include <errno.h>

static void dummy_sample_cb(void *ctx, int cpu, void *data, __u32 size) {
}

static void dummy_lost_cb(void *ctx, int cpu, __u64 cnt) {
}

int LLVMFuzzerTestOneInput_73(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) + sizeof(size_t)) {
        return 0;
    }

    int map_fd = *(int *)Data;
    size_t page_cnt = *(size_t *)(Data + sizeof(int));

    struct perf_buffer_opts opts = {
        .sz = sizeof(struct perf_buffer_opts),
        .sample_period = 1,
    };

    struct perf_buffer *pb = perf_buffer__new(map_fd, page_cnt, dummy_sample_cb, dummy_lost_cb, NULL, &opts);
    if (!pb) {
        return 0;
    }

    int ret;
    ret = perf_buffer__consume(pb);
    if (ret < 0) {
        perf_buffer__free(pb);
        return 0;
    }

    size_t buf_idx = 0;
    ret = perf_buffer__buffer_fd(pb, buf_idx);
    if (ret < 0) {
        perf_buffer__free(pb);
        return 0;
    }

    ret = perf_buffer__epoll_fd(pb);
    if (ret < 0) {
        perf_buffer__free(pb);
        return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from perf_buffer__epoll_fd to libbpf_strerror
    size_t ret_perf_buffer__buffer_cnt_antls = perf_buffer__buffer_cnt(pb);
    if (ret_perf_buffer__buffer_cnt_antls < 0){
    	return 0;
    }
    char wlmkzmpk[1024] = "owdba";

    int ret_libbpf_strerror_bnhgy = libbpf_strerror((int )ret_perf_buffer__buffer_cnt_antls, wlmkzmpk, (size_t )ret);
    if (ret_libbpf_strerror_bnhgy < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    ret = perf_buffer__consume_buffer(pb, buf_idx);
    if (ret < 0) {
        perf_buffer__free(pb);
        return 0;
    }

    void *buf;
    size_t buf_size;
    ret = perf_buffer__buffer(pb, buf_idx, &buf, &buf_size);
    if (ret < 0) {
        perf_buffer__free(pb);
        return 0;
    }

    perf_buffer__free(pb);
    return 0;
}