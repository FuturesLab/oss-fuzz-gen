#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

typedef enum {
    BPF_ATTACH_TYPE_UNSPEC = 0,
    BPF_ATTACH_TYPE_CGROUP_INET_INGRESS,
    BPF_ATTACH_TYPE_CGROUP_INET_EGRESS,
    BPF_ATTACH_TYPE_CGROUP_INET_SOCK_CREATE,
    BPF_ATTACH_TYPE_CGROUP_SOCK_OPS,
    BPF_ATTACH_TYPE_SK_SKB_STREAM_PARSER,
    BPF_ATTACH_TYPE_SK_SKB_STREAM_VERDICT,
    BPF_ATTACH_TYPE_CGROUP_DEVICE,
    BPF_ATTACH_TYPE_SK_MSG_VERDICT,
    BPF_ATTACH_TYPE_CGROUP_INET4_BIND,
    BPF_ATTACH_TYPE_CGROUP_INET6_BIND,
    BPF_ATTACH_TYPE_CGROUP_INET4_CONNECT,
    BPF_ATTACH_TYPE_CGROUP_INET6_CONNECT,
    BPF_ATTACH_TYPE_CGROUP_INET4_POST_BIND,
    BPF_ATTACH_TYPE_CGROUP_INET6_POST_BIND,
    BPF_ATTACH_TYPE_CGROUP_UDP4_SENDMSG,
    BPF_ATTACH_TYPE_CGROUP_UDP6_SENDMSG,
    BPF_ATTACH_TYPE_LIRC_MODE2,
    BPF_ATTACH_TYPE_FLOW_DISSECTOR,
    BPF_ATTACH_TYPE_CGROUP_SYSCTL,
    BPF_ATTACH_TYPE_CGROUP_UDP4_RECVMSG,
    BPF_ATTACH_TYPE_CGROUP_UDP6_RECVMSG,
    BPF_ATTACH_TYPE_CGROUP_GETSOCKOPT,
    BPF_ATTACH_TYPE_CGROUP_SETSOCKOPT,
    BPF_ATTACH_TYPE_TRACE_RAW_TP,
    BPF_ATTACH_TYPE_TRACE_FENTRY,
    BPF_ATTACH_TYPE_TRACE_FEXIT,
    BPF_ATTACH_TYPE_MODIFY_RETURN,
    BPF_ATTACH_TYPE_LSM_MAC,
    BPF_ATTACH_TYPE_KPROBE_MULTI,
    __MAX_BPF_ATTACH_TYPE
} DW_TAG_enumeration_typebpf_attach_type;

extern int libbpf_find_vmlinux_btf_id(const char *, DW_TAG_enumeration_typebpf_attach_type);

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    
    // Write the fuzz data to the temporary file
    write(fd, data, size);
    close(fd);

    // Iterate over different BPF attach types
    for (int attach_type = BPF_ATTACH_TYPE_UNSPEC; attach_type < __MAX_BPF_ATTACH_TYPE; attach_type++) {
        libbpf_find_vmlinux_btf_id(tmpl, (DW_TAG_enumeration_typebpf_attach_type)attach_type);
    }

    // Clean up the temporary file
    unlink(tmpl);

    return 0;
}