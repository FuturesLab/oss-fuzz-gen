#include <stdint.h>
#include <stddef.h>
#include "libdwarf.h"
#include <stdio.h>

int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    if (size < sizeof(Dwarf_Unsigned)) {
        return 0;
    }

    Dwarf_Unsigned errnum;
    // Copy the data into errnum ensuring it does not exceed the size of Dwarf_Unsigned
    errnum = *(const Dwarf_Unsigned *)data;

    // Call the function-under-test
    char *errmsg = dwarf_errmsg_by_number(errnum);

    // Optionally print the error message for debugging purposes
    if (errmsg != NULL) {

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from dwarf_errmsg_by_number to dwarf_get_fde_instr_bytes
    int ret_dwarf_library_allow_dup_attr_sbtop = dwarf_library_allow_dup_attr(DW_DLE_LINE_NUMBER_HEADER_ERROR);
    if (ret_dwarf_library_allow_dup_attr_sbtop < 0){
    	return 0;
    }
    Dwarf_Error wnzatqjb;
    memset(&wnzatqjb, 0, sizeof(wnzatqjb));

    int ret_dwarf_get_fde_instr_bytes_ngclb = dwarf_get_fde_instr_bytes(0, (unsigned char )*errmsg, (unsigned long long )ret_dwarf_library_allow_dup_attr_sbtop, &wnzatqjb);
    if (ret_dwarf_get_fde_instr_bytes_ngclb < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from dwarf_get_fde_instr_bytes to dwarf_next_str_offsets_table

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from dwarf_get_fde_instr_bytes to dwarf_str_offsets_value_by_index
    Dwarf_Half ret_dwarf_global_tag_number_juwxc = dwarf_global_tag_number(0);
    if (ret_dwarf_global_tag_number_juwxc < 0){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from dwarf_global_tag_number to dwarf_srclines_subprog_data
    char* ret_dwarf_errmsg_by_number_gekvi = dwarf_errmsg_by_number(DW_DLE_LINE_NUM_OPERANDS_BAD);
    if (ret_dwarf_errmsg_by_number_gekvi == NULL){
    	return 0;
    }
    Dwarf_Unsigned vfhuqqxn = 1;

    int ret_dwarf_srclines_subprog_data_bbjyo = dwarf_srclines_subprog_data(0, 0, &ret_dwarf_errmsg_by_number_gekvi, &vfhuqqxn, (unsigned long long )ret_dwarf_global_tag_number_juwxc, &wnzatqjb);
    if (ret_dwarf_srclines_subprog_data_bbjyo < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_dwarf_str_offsets_value_by_index_hjsdk = dwarf_str_offsets_value_by_index(0, DW_DLE_GROUPNUMBER_ERROR, (unsigned long long )ret_dwarf_global_tag_number_juwxc, &wnzatqjb);
    if (ret_dwarf_str_offsets_value_by_index_hjsdk < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_dwarf_suppress_debuglink_crc_fjxtd = dwarf_suppress_debuglink_crc(DW_DLE_ELF_SECTION_LINK_ERROR);
    if (ret_dwarf_suppress_debuglink_crc_fjxtd < 0){
    	return 0;
    }
    int ret_dwarf_set_reloc_application_iiavj = dwarf_set_reloc_application(DW_DLE_DEBUG_WEAKNAMES_DUPLICATE);
    if (ret_dwarf_set_reloc_application_iiavj < 0){
    	return 0;
    }
    int ret_dwarf_set_reloc_application_szcjk = dwarf_set_reloc_application(DW_DLE_DEBUG_LINE_STR_DUPLICATE);
    if (ret_dwarf_set_reloc_application_szcjk < 0){
    	return 0;
    }
    int ret_dwarf_library_allow_dup_attr_wxnwi = dwarf_library_allow_dup_attr(DW_DLE_GDB_INDEX_COUNT_ADDR_ERROR);
    if (ret_dwarf_library_allow_dup_attr_wxnwi < 0){
    	return 0;
    }
    int ret_dwarf_library_allow_dup_attr_tonnn = dwarf_library_allow_dup_attr(DW_DLE_ELF_STRING_SECTION_MISSING);
    if (ret_dwarf_library_allow_dup_attr_tonnn < 0){
    	return 0;
    }
    int ret_dwarf_set_de_alloc_flag_gxotl = dwarf_set_de_alloc_flag(DW_DLE_INCDIR_ALLOC);
    if (ret_dwarf_set_de_alloc_flag_gxotl < 0){
    	return 0;
    }

    int ret_dwarf_next_str_offsets_table_hnghv = dwarf_next_str_offsets_table(0, (unsigned long long )ret_dwarf_suppress_debuglink_crc_fjxtd, (unsigned long long )ret_dwarf_set_reloc_application_iiavj, (unsigned long long )ret_dwarf_library_allow_dup_attr_sbtop, (unsigned short )ret_dwarf_set_reloc_application_szcjk, (unsigned short )ret_dwarf_library_allow_dup_attr_wxnwi, (unsigned short )ret_dwarf_library_allow_dup_attr_tonnn, (unsigned long long )ret_dwarf_set_de_alloc_flag_gxotl, &wnzatqjb);
    if (ret_dwarf_next_str_offsets_table_hnghv < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from dwarf_errmsg_by_number to dwarf_gnu_debuglink
    char* ret_dwarf_find_macro_value_start_blntr = dwarf_find_macro_value_start((char *)"w");
    if (ret_dwarf_find_macro_value_start_blntr == NULL){
    	return 0;
    }
    int ret_dwarf_set_reloc_application_fenlm = dwarf_set_reloc_application(DW_DLE_SIGNATURE_MISMATCH);
    if (ret_dwarf_set_reloc_application_fenlm < 0){
    	return 0;
    }
    int ret_dwarf_set_stringcheck_xgwcm = dwarf_set_stringcheck(DW_DLE_BAD_TYPE_SIZE);
    if (ret_dwarf_set_stringcheck_xgwcm < 0){
    	return 0;
    }
    char* ret_dwarf_find_macro_value_start_pcxql = dwarf_find_macro_value_start(errmsg);
    if (ret_dwarf_find_macro_value_start_pcxql == NULL){
    	return 0;
    }
    Dwarf_Bool ret_dwarf_addr_form_is_indexed_snnou = dwarf_addr_form_is_indexed(DW_DLE_NO_COMP_DIR);
    if (ret_dwarf_addr_form_is_indexed_snnou < 0){
    	return 0;
    }
    unsigned int jtoahgbv = 1;

    int ret_dwarf_gnu_debuglink_kjemw = dwarf_gnu_debuglink(0, &ret_dwarf_find_macro_value_start_blntr, (unsigned char **)&errmsg, (char **)"r", (unsigned int *)&ret_dwarf_set_reloc_application_fenlm, (unsigned int *)&ret_dwarf_set_stringcheck_xgwcm, (char **)data, (unsigned char **)&ret_dwarf_find_macro_value_start_pcxql, (unsigned int *)&ret_dwarf_addr_form_is_indexed_snnou, (char ***)data, &jtoahgbv, NULL);
    if (ret_dwarf_gnu_debuglink_kjemw < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

        printf("Error message: %s\n", errmsg);
    }

    return 0;
}