// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Aiterate2 at H5A.c:1855:1 in H5Apublic.h
// H5Aiterate_by_name at H5A.c:1942:1 in H5Apublic.h
// H5Aiterate_by_name at H5A.c:1942:1 in H5Apublic.h
// H5Aiterate2 at H5A.c:1855:1 in H5Apublic.h
// H5Aiterate_by_name at H5A.c:1942:1 in H5Apublic.h
// H5Aiterate_by_name at H5A.c:1942:1 in H5Apublic.h
// H5Aiterate1 at H5Adeprec.c:373:1 in H5Apublic.h
// H5Aiterate2 at H5A.c:1855:1 in H5Apublic.h
// H5Aiterate_by_name at H5A.c:1942:1 in H5Apublic.h
// H5Aiterate_by_name at H5A.c:1942:1 in H5Apublic.h
// H5Aiterate1 at H5Adeprec.c:373:1 in H5Apublic.h
// H5Aiterate2 at H5A.c:1855:1 in H5Apublic.h
// H5Aiterate_by_name at H5A.c:1942:1 in H5Apublic.h
// H5Aiterate_by_name at H5A.c:1942:1 in H5Apublic.h
// H5Aiterate1 at H5Adeprec.c:373:1 in H5Apublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "H5Apublic.h"

static herr_t dummy_operator(hid_t location_id, const char *attr_name, const H5A_info_t *ainfo, void *op_data) {
    return 0; // Dummy operator function for iteration
}

int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t) + sizeof(hsize_t) + sizeof(hid_t)) {
        return 0;
    }

    hid_t loc_id = *((const hid_t *)Data);
    Data += sizeof(hid_t);
    Size -= sizeof(hid_t);

    hsize_t idx = *((const hsize_t *)Data);
    Data += sizeof(hsize_t);
    Size -= sizeof(hsize_t);

    hid_t lapl_id = *((const hid_t *)Data);
    Data += sizeof(hid_t);
    Size -= sizeof(hid_t);

    const char *obj_name = "./dummy_file";
    H5_index_t idx_type = H5_INDEX_NAME;
    H5_iter_order_t order = H5_ITER_INC;

    herr_t ret;

    ret = H5Aiterate2(loc_id, idx_type, order, &idx, dummy_operator, NULL);
    if (ret < 0) {
        fprintf(stderr, "H5Aiterate2 failed\n");
    }

    ret = H5Aiterate_by_name(loc_id, obj_name, idx_type, order, &idx, dummy_operator, NULL, lapl_id);
    if (ret < 0) {
        fprintf(stderr, "H5Aiterate_by_name failed\n");
    }

    ret = H5Aiterate_by_name(loc_id, obj_name, idx_type, order, &idx, dummy_operator, NULL, lapl_id);
    if (ret < 0) {
        fprintf(stderr, "H5Aiterate_by_name failed\n");
    }

    unsigned idx1 = (unsigned)idx;
    ret = H5Aiterate1(loc_id, &idx1, (H5A_operator1_t)dummy_operator, NULL);
    if (ret < 0) {
        fprintf(stderr, "H5Aiterate1 failed\n");
    }

    ret = H5Aiterate2(loc_id, idx_type, order, &idx, dummy_operator, NULL);
    if (ret < 0) {
        fprintf(stderr, "H5Aiterate2 failed\n");
    }

    ret = H5Aiterate_by_name(loc_id, obj_name, idx_type, order, &idx, dummy_operator, NULL, lapl_id);
    if (ret < 0) {
        fprintf(stderr, "H5Aiterate_by_name failed\n");
    }

    ret = H5Aiterate_by_name(loc_id, obj_name, idx_type, order, &idx, dummy_operator, NULL, lapl_id);
    if (ret < 0) {
        fprintf(stderr, "H5Aiterate_by_name failed\n");
    }

    idx1 = (unsigned)idx;
    ret = H5Aiterate1(loc_id, &idx1, (H5A_operator1_t)dummy_operator, NULL);
    if (ret < 0) {
        fprintf(stderr, "H5Aiterate1 failed\n");
    }

    ret = H5Aiterate2(loc_id, idx_type, order, &idx, dummy_operator, NULL);
    if (ret < 0) {
        fprintf(stderr, "H5Aiterate2 failed\n");
    }

    ret = H5Aiterate_by_name(loc_id, obj_name, idx_type, order, &idx, dummy_operator, NULL, lapl_id);
    if (ret < 0) {
        fprintf(stderr, "H5Aiterate_by_name failed\n");
    }

    ret = H5Aiterate_by_name(loc_id, obj_name, idx_type, order, &idx, dummy_operator, NULL, lapl_id);
    if (ret < 0) {
        fprintf(stderr, "H5Aiterate_by_name failed\n");
    }

    idx1 = (unsigned)idx;
    ret = H5Aiterate1(loc_id, &idx1, (H5A_operator1_t)dummy_operator, NULL);
    if (ret < 0) {
        fprintf(stderr, "H5Aiterate1 failed\n");
    }

    ret = H5Aiterate2(loc_id, idx_type, order, &idx, dummy_operator, NULL);
    if (ret < 0) {
        fprintf(stderr, "H5Aiterate2 failed\n");
    }

    ret = H5Aiterate_by_name(loc_id, obj_name, idx_type, order, &idx, dummy_operator, NULL, lapl_id);
    if (ret < 0) {
        fprintf(stderr, "H5Aiterate_by_name failed\n");
    }

    ret = H5Aiterate_by_name(loc_id, obj_name, idx_type, order, &idx, dummy_operator, NULL, lapl_id);
    if (ret < 0) {
        fprintf(stderr, "H5Aiterate_by_name failed\n");
    }

    return 0;
}