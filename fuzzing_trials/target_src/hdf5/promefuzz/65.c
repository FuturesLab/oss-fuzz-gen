// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dfill at H5D.c:1758:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dget_access_plist at H5D.c:805:1 in H5Dpublic.h
// H5Dget_space_status at H5D.c:668:1 in H5Dpublic.h
// H5Dvlen_reclaim at H5Ddeprec.c:304:1 in H5Dpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
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

#define DUMMY_FILE "./dummy_file"

static hid_t create_dummy_dataset() {
    hid_t file_id, dataset_id, space_id;
    hsize_t dims[1] = {10};
    herr_t status;

    file_id = H5Fcreate(DUMMY_FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return file_id;

    space_id = H5Screate_simple(1, dims, NULL);
    if (space_id < 0) {
        H5Fclose(file_id);
        return space_id;
    }

    dataset_id = H5Dcreate2(file_id, "dummy_dataset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return dataset_id;
    }

    status = H5Sclose(space_id);
    if (status < 0) {
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return status;
    }

    status = H5Fclose(file_id);
    if (status < 0) {
        H5Dclose(dataset_id);
        return status;
    }

    return dataset_id;
}

int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    herr_t status;
    hid_t dataset_id = create_dummy_dataset();
    if (dataset_id < 0) return 0;

    int fill_value = 0;
    if (Size >= sizeof(int)) {
        memcpy(&fill_value, Data, sizeof(int));
    }

    hid_t fill_type_id = H5T_NATIVE_INT;
    int buffer[10] = {0};
    hid_t buf_type_id = H5T_NATIVE_INT;
    hid_t space_id = H5S_ALL;

    // H5Dfill
    status = H5Dfill(&fill_value, fill_type_id, buffer, buf_type_id, space_id);
    if (status < 0) {
        H5Dclose(dataset_id);
        return 0;
    }

    // H5Dget_access_plist
    hid_t plist_id = H5Dget_access_plist(dataset_id);
    if (plist_id >= 0) {
        H5Pclose(plist_id);
    }

    // H5Dget_space_status
    H5D_space_status_t allocation;
    status = H5Dget_space_status(dataset_id, &allocation);

    // H5Dvlen_reclaim
    status = H5Dvlen_reclaim(fill_type_id, space_id, H5P_DEFAULT, buffer);

    // H5Dwrite
    status = H5Dwrite(dataset_id, fill_type_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, buffer);

    // H5Dread
    status = H5Dread(dataset_id, fill_type_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, buffer);

    H5Dclose(dataset_id);
    return 0;
}