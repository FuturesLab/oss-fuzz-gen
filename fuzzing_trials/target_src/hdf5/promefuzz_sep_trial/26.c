// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Aopen at H5A.c:531:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Adelete at H5A.c:2008:1 in H5Apublic.h
// H5Acreate_by_name at H5A.c:366:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Adelete_by_name at H5A.c:2066:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "H5Apublic.h"
#include "H5Fpublic.h"
#include "H5Ppublic.h"
#include "H5Tpublic.h"
#include "H5Spublic.h"

static hid_t create_dummy_file() {
    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        fprintf(stderr, "Failed to create dummy file.\n");
        exit(EXIT_FAILURE);
    }
    return file_id;
}

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    hid_t file_id = create_dummy_file();
    hid_t attr_id = -1;
    herr_t status;

    // Use Data for attribute and object names
    char obj_name[100];
    char attr_name[100];
    snprintf(obj_name, sizeof(obj_name), "obj_%zu", Size);
    snprintf(attr_name, sizeof(attr_name), "attr_%zu", Size);

    // Create a datatype and dataspace for the attribute
    hid_t type_id = H5Tcopy(H5T_NATIVE_INT);
    hid_t space_id = H5Screate(H5S_SCALAR);

    if (type_id < 0 || space_id < 0) {
        fprintf(stderr, "Failed to create datatype or dataspace.\n");
        goto cleanup;
    }

    // H5Aopen
    attr_id = H5Aopen(file_id, attr_name, H5P_DEFAULT);
    if (attr_id >= 0) {
        // H5Aclose
        status = H5Aclose(attr_id);
        if (status < 0) {
            fprintf(stderr, "Failed to close attribute.\n");
        }
    }

    // H5Adelete
    status = H5Adelete(file_id, attr_name);
    if (status < 0) {
        fprintf(stderr, "Failed to delete attribute.\n");
    }

    // H5Acreate_by_name
    attr_id = H5Acreate_by_name(file_id, obj_name, attr_name, type_id, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id >= 0) {
        // H5Aclose
        status = H5Aclose(attr_id);
        if (status < 0) {
            fprintf(stderr, "Failed to close attribute.\n");
        }
    }

    // H5Adelete_by_name
    status = H5Adelete_by_name(file_id, obj_name, attr_name, H5P_DEFAULT);
    if (status < 0) {
        fprintf(stderr, "Failed to delete attribute by name.\n");
    }

    // H5Fclose twice
    status = H5Fclose(file_id);
    if (status < 0) {
        fprintf(stderr, "Failed to close file.\n");
    }
    status = H5Fclose(file_id);
    if (status < 0) {
        fprintf(stderr, "Failed to close file.\n");
    }

    // H5Aclose twice
    status = H5Aclose(attr_id);
    if (status < 0) {
        fprintf(stderr, "Failed to close attribute.\n");
    }
    status = H5Aclose(attr_id);
    if (status < 0) {
        fprintf(stderr, "Failed to close attribute.\n");
    }

cleanup:
    if (type_id >= 0) H5Tclose(type_id);
    if (space_id >= 0) H5Sclose(space_id);
    return 0;
}