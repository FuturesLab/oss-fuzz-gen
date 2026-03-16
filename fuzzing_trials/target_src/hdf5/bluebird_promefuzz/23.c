// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Acreate2 at H5A.c:221:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Arename at H5A.c:1646:1 in H5Apublic.h
// H5Arename at H5A.c:1646:1 in H5Apublic.h
// H5Arename at H5A.c:1646:1 in H5Apublic.h
// H5Arename at H5A.c:1646:1 in H5Apublic.h
// H5Arename_by_name at H5A.c:1756:1 in H5Apublic.h
// H5Arename_by_name at H5A.c:1756:1 in H5Apublic.h
// H5Arename_by_name at H5A.c:1756:1 in H5Apublic.h
// H5Arename_by_name at H5A.c:1756:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "H5Apublic.h"
#include "H5Fpublic.h"
#include "H5Spublic.h"
#include "H5Tpublic.h"
#include "H5Ppublic.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fputs("dummy content", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    write_dummy_file();

    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    hid_t space_id = H5Screate(H5S_SCALAR);
    if (space_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    hid_t attr_id = H5Acreate2(file_id, "attr", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    H5Sclose(space_id);

    H5Arename(file_id, "attr", "new_attr");
    H5Arename(file_id, "new_attr", "new_attr2");
    H5Arename(file_id, "new_attr2", "new_attr3");
    H5Arename(file_id, "new_attr3", "new_attr4");

    H5Arename_by_name(file_id, ".", "new_attr4", "final_attr", H5P_DEFAULT);
    H5Arename_by_name(file_id, ".", "final_attr", "final_attr2", H5P_DEFAULT);
    H5Arename_by_name(file_id, ".", "final_attr2", "final_attr3", H5P_DEFAULT);
    H5Arename_by_name(file_id, ".", "final_attr3", "final_attr4", H5P_DEFAULT);

    H5Aclose(attr_id);
    H5Fclose(file_id);

    return 0;
}