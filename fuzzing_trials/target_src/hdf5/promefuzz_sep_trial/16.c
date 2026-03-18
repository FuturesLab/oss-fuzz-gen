// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
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
// H5Aiterate2 at H5A.c:1855:1 in H5Apublic.h
// H5Aiterate_by_name at H5A.c:1942:1 in H5Apublic.h
// H5Aiterate_by_name at H5A.c:1942:1 in H5Apublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <hdf5.h>
#include <H5Apublic.h>

static herr_t dummy_operator(hid_t location_id, const char *attr_name, const H5A_info_t *ainfo, void *op_data) {
    // Dummy operator function for iteration
    return 0;
}

static herr_t dummy_operator1(hid_t location_id, const char *attr_name, void *op_data) {
    // Dummy operator function for iteration
    return 0;
}

int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t) + sizeof(H5_index_t) + sizeof(H5_iter_order_t) + sizeof(hsize_t)) {
        return 0;
    }

    // Initialize variables
    hid_t loc_id = *(const hid_t *)Data;
    Data += sizeof(hid_t);
    Size -= sizeof(hid_t);

    H5_index_t idx_type = *(const H5_index_t *)Data;
    Data += sizeof(H5_index_t);
    Size -= sizeof(H5_index_t);

    H5_iter_order_t order = *(const H5_iter_order_t *)Data;
    Data += sizeof(H5_iter_order_t);
    Size -= sizeof(H5_iter_order_t);

    hsize_t idx = *(const hsize_t *)Data;
    Data += sizeof(hsize_t);
    Size -= sizeof(hsize_t);

    // Prepare dummy data for H5Aiterate_by_name
    const char *obj_name = "dummy_object";
    hid_t lapl_id = H5P_DEFAULT;

    // Iterate over attributes using the provided functions
    H5Aiterate2(loc_id, idx_type, order, &idx, dummy_operator, NULL);
    H5Aiterate_by_name(loc_id, obj_name, idx_type, order, &idx, dummy_operator, NULL, lapl_id);
    H5Aiterate_by_name(loc_id, obj_name, idx_type, order, &idx, dummy_operator, NULL, lapl_id);
    H5Aiterate1(loc_id, (unsigned *)&idx, dummy_operator1, NULL);

    H5Aiterate2(loc_id, idx_type, order, &idx, dummy_operator, NULL);
    H5Aiterate_by_name(loc_id, obj_name, idx_type, order, &idx, dummy_operator, NULL, lapl_id);
    H5Aiterate_by_name(loc_id, obj_name, idx_type, order, &idx, dummy_operator, NULL, lapl_id);
    H5Aiterate1(loc_id, (unsigned *)&idx, dummy_operator1, NULL);

    H5Aiterate2(loc_id, idx_type, order, &idx, dummy_operator, NULL);
    H5Aiterate_by_name(loc_id, obj_name, idx_type, order, &idx, dummy_operator, NULL, lapl_id);
    H5Aiterate_by_name(loc_id, obj_name, idx_type, order, &idx, dummy_operator, NULL, lapl_id);
    H5Aiterate1(loc_id, (unsigned *)&idx, dummy_operator1, NULL);

    H5Aiterate2(loc_id, idx_type, order, &idx, dummy_operator, NULL);
    H5Aiterate_by_name(loc_id, obj_name, idx_type, order, &idx, dummy_operator, NULL, lapl_id);
    H5Aiterate_by_name(loc_id, obj_name, idx_type, order, &idx, dummy_operator, NULL, lapl_id);

    return 0;
}