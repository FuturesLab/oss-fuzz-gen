// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fget_create_plist at H5F.c:106:1 in H5Fpublic.h
// H5Fget_access_plist at H5F.c:152:1 in H5Fpublic.h
// H5Fget_name at H5F.c:1999:1 in H5Fpublic.h
// H5Fget_obj_count at H5F.c:216:1 in H5Fpublic.h
// H5Fget_obj_ids at H5F.c:333:1 in H5Fpublic.h
// H5Fget_vfd_handle at H5F.c:422:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "H5Fpublic.h"
#include "H5Ppublic.h"

static hid_t create_dummy_file() {
    hid_t file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) {
        file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    }
    return file_id;
}

int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t)) return 0;

    hid_t file_id = create_dummy_file();
    if (file_id < 0) return 0;

    // Fuzz H5Fget_create_plist
    hid_t plist_id = H5Fget_create_plist(file_id);
    if (plist_id >= 0) {
        H5Pclose(plist_id);
    }

    // Fuzz H5Fget_access_plist
    plist_id = H5Fget_access_plist(file_id);
    if (plist_id >= 0) {
        H5Pclose(plist_id);
    }

    // Fuzz H5Fget_name
    char name[1024];
    ssize_t name_len = H5Fget_name(file_id, name, sizeof(name));
    if (name_len >= 0) {
        // Successfully retrieved the file name
    }

    // Fuzz H5Fget_obj_count
    unsigned types = *(unsigned *)Data;
    ssize_t obj_count = H5Fget_obj_count(file_id, types);
    if (obj_count >= 0) {
        // Successfully retrieved the object count
    }

    // Fuzz H5Fget_obj_ids
    hid_t obj_id_list[10];
    ssize_t obj_ids_count = H5Fget_obj_ids(file_id, types, 10, obj_id_list);
    if (obj_ids_count >= 0) {
        // Successfully retrieved the object IDs
    }

    // Fuzz H5Fget_vfd_handle
    void *file_handle = NULL;
    herr_t status = H5Fget_vfd_handle(file_id, H5P_DEFAULT, &file_handle);
    if (status >= 0 && file_handle != NULL) {
        // Successfully retrieved the VFD handle
    }

    H5Fclose(file_id);
    return 0;
}