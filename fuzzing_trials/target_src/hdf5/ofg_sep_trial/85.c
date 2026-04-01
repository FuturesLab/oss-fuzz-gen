#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t loc_id = H5I_INVALID_HID;
    hid_t file_id = H5I_INVALID_HID;
    hid_t space_id = H5I_INVALID_HID;
    hid_t attr_id = H5I_INVALID_HID;
    hid_t lapl_id = H5P_DEFAULT;
    char *obj_name = NULL;
    char *attr_name = NULL;

    // Ensure size is sufficient for at least two strings
    if (size < 4) {
        return 0;
    }

    // Split the data into two strings
    size_t obj_name_len = data[0] % (size - 2) + 1;
    size_t attr_name_len = data[1] % (size - obj_name_len - 1) + 1;

    // Allocate memory for the strings
    obj_name = (char *)malloc(obj_name_len + 1);
    attr_name = (char *)malloc(attr_name_len + 1);

    if (obj_name == NULL || attr_name == NULL) {
        free(obj_name);
        free(attr_name);
        return 0;
    }

    // Copy data into the strings and null-terminate them
    memcpy(obj_name, data + 2, obj_name_len);
    obj_name[obj_name_len] = '\0';

    memcpy(attr_name, data + 2 + obj_name_len, attr_name_len);
    attr_name[attr_name_len] = '\0';

    // Ensure obj_name and attr_name are not empty
    if (obj_name_len == 0 || attr_name_len == 0) {
        free(obj_name);
        free(attr_name);
        return 0;
    }

    // Initialize HDF5 library
    H5open();

    // Create a temporary file to get a valid loc_id
    file_id = H5Fcreate("temp.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id >= 0) {
        loc_id = file_id;

        // Create a dataspace for the attribute
        space_id = H5Screate(H5S_SCALAR);

        if (space_id >= 0) {
            // Create an object in the file (a group in this case)
            hid_t group_id = H5Gcreate(loc_id, obj_name, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
            if (group_id >= 0) {
                // Create an attribute for the object
                attr_id = H5Acreate(group_id, attr_name, H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT);
                if (attr_id >= 0) {
                    // Close the attribute
                    H5Aclose(attr_id);
                }
                // Close the group
                H5Gclose(group_id);
            }
            // Close the dataspace
            H5Sclose(space_id);
        }

        // Call the function-under-test only if obj_name and attr_name are not empty
        if (obj_name_len > 0 && attr_name_len > 0) {
            H5Adelete_by_name(loc_id, obj_name, attr_name, lapl_id);
        }

        // Close the file
        H5Fclose(file_id);
    }

    // Close HDF5 library
    H5close();

    // Free allocated memory
    free(obj_name);
    free(attr_name);

    return 0;
}