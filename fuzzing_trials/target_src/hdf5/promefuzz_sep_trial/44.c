// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fget_create_plist at H5F.c:106:1 in H5Fpublic.h
// H5Fget_intent at H5F.c:1540:1 in H5Fpublic.h
// H5Fget_access_plist at H5F.c:152:1 in H5Fpublic.h
// H5Fget_obj_count at H5F.c:216:1 in H5Fpublic.h
// H5Fget_obj_ids at H5F.c:333:1 in H5Fpublic.h
// H5Fget_vfd_handle at H5F.c:422:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

static hid_t open_hdf5_file(const char *filename) {
    hid_t file_id = H5Fopen(filename, H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) {
        file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    }
    return file_id;
}

static void close_hdf5_file(hid_t file_id) {
    if (file_id >= 0) {
        H5Fclose(file_id);
    }
}

int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned) + sizeof(size_t)) {
        return 0;
    }

    unsigned types = *(unsigned *)Data;
    size_t max_objs = *(size_t *)(Data + sizeof(unsigned));

    hid_t file_id = open_hdf5_file("./dummy_file");
    if (file_id < 0) {
        return 0;
    }

    // Fuzz H5Fget_create_plist
    hid_t plist_id = H5Fget_create_plist(file_id);
    if (plist_id >= 0) {
        H5Pclose(plist_id);
    }

    // Fuzz H5Fget_intent
    unsigned intent;
    H5Fget_intent(file_id, &intent);

    // Fuzz H5Fget_access_plist
    hid_t access_plist_id = H5Fget_access_plist(file_id);
    if (access_plist_id >= 0) {
        H5Pclose(access_plist_id);
    }

    // Fuzz H5Fget_obj_count
    ssize_t obj_count = H5Fget_obj_count(file_id, types);

    // Fuzz H5Fget_obj_ids
    if (obj_count > 0) {
        hid_t *obj_id_list = (hid_t *)malloc(obj_count * sizeof(hid_t));
        if (obj_id_list) {
            H5Fget_obj_ids(file_id, types, max_objs, obj_id_list);
            free(obj_id_list);
        }
    }

    // Fuzz H5Fget_vfd_handle
    void *file_handle;
    H5Fget_vfd_handle(file_id, H5P_DEFAULT, &file_handle);

    close_hdf5_file(file_id);
    return 0;
}