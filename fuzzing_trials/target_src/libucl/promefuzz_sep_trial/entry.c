// This is the entry of 68 fuzz drivers:
// 1, 2, 3, 5, 6, 7, 9, 11, 12, 13, 15, 17, 18, 21, 22, 23, 24, 25, 26, 27, 29, 30,
//  31, 34, 35, 36, 41, 42, 43, 44, 45, 46, 49, 50, 52, 53, 54, 56, 57, 58, 59, 60,
//  61, 62, 63, 64, 66, 67, 69, 70, 72, 75, 77, 78, 79, 82, 84, 88, 89, 90, 91, 93,
//  94, 103, 105, 108, 109, 115
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <memory.h>

// Declarations of all fuzz drivers `LLVMFuzzerTestOneInput` functions
int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_69(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_72(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_77(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_78(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_88(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_89(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_91(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_93(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_105(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_108(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_109(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_115(const uint8_t *Data, size_t Size);

// Entry function
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    // Driver selector
    if (Size < 1) {
        return 0;
    }
    const uint8_t *selector = Data;
    unsigned int driverIndex = 0;
    memcpy(&driverIndex, selector, 1);

    // Remain data and size
    const uint8_t *remainData = Data + 1;
    size_t remainSize = Size - 1;
    if (remainSize == 0) {
        return 0;
    }

    // Select driver
    switch (driverIndex % 68) {
        case 0:
            return LLVMFuzzerTestOneInput_1(remainData, remainSize);
        case 1:
            return LLVMFuzzerTestOneInput_2(remainData, remainSize);
        case 2:
            return LLVMFuzzerTestOneInput_3(remainData, remainSize);
        case 3:
            return LLVMFuzzerTestOneInput_5(remainData, remainSize);
        case 4:
            return LLVMFuzzerTestOneInput_6(remainData, remainSize);
        case 5:
            return LLVMFuzzerTestOneInput_7(remainData, remainSize);
        case 6:
            return LLVMFuzzerTestOneInput_9(remainData, remainSize);
        case 7:
            return LLVMFuzzerTestOneInput_11(remainData, remainSize);
        case 8:
            return LLVMFuzzerTestOneInput_12(remainData, remainSize);
        case 9:
            return LLVMFuzzerTestOneInput_13(remainData, remainSize);
        case 10:
            return LLVMFuzzerTestOneInput_15(remainData, remainSize);
        case 11:
            return LLVMFuzzerTestOneInput_17(remainData, remainSize);
        case 12:
            return LLVMFuzzerTestOneInput_18(remainData, remainSize);
        case 13:
            return LLVMFuzzerTestOneInput_21(remainData, remainSize);
        case 14:
            return LLVMFuzzerTestOneInput_22(remainData, remainSize);
        case 15:
            return LLVMFuzzerTestOneInput_23(remainData, remainSize);
        case 16:
            return LLVMFuzzerTestOneInput_24(remainData, remainSize);
        case 17:
            return LLVMFuzzerTestOneInput_25(remainData, remainSize);
        case 18:
            return LLVMFuzzerTestOneInput_26(remainData, remainSize);
        case 19:
            return LLVMFuzzerTestOneInput_27(remainData, remainSize);
        case 20:
            return LLVMFuzzerTestOneInput_29(remainData, remainSize);
        case 21:
            return LLVMFuzzerTestOneInput_30(remainData, remainSize);
        case 22:
            return LLVMFuzzerTestOneInput_31(remainData, remainSize);
        case 23:
            return LLVMFuzzerTestOneInput_34(remainData, remainSize);
        case 24:
            return LLVMFuzzerTestOneInput_35(remainData, remainSize);
        case 25:
            return LLVMFuzzerTestOneInput_36(remainData, remainSize);
        case 26:
            return LLVMFuzzerTestOneInput_41(remainData, remainSize);
        case 27:
            return LLVMFuzzerTestOneInput_42(remainData, remainSize);
        case 28:
            return LLVMFuzzerTestOneInput_43(remainData, remainSize);
        case 29:
            return LLVMFuzzerTestOneInput_44(remainData, remainSize);
        case 30:
            return LLVMFuzzerTestOneInput_45(remainData, remainSize);
        case 31:
            return LLVMFuzzerTestOneInput_46(remainData, remainSize);
        case 32:
            return LLVMFuzzerTestOneInput_49(remainData, remainSize);
        case 33:
            return LLVMFuzzerTestOneInput_50(remainData, remainSize);
        case 34:
            return LLVMFuzzerTestOneInput_52(remainData, remainSize);
        case 35:
            return LLVMFuzzerTestOneInput_53(remainData, remainSize);
        case 36:
            return LLVMFuzzerTestOneInput_54(remainData, remainSize);
        case 37:
            return LLVMFuzzerTestOneInput_56(remainData, remainSize);
        case 38:
            return LLVMFuzzerTestOneInput_57(remainData, remainSize);
        case 39:
            return LLVMFuzzerTestOneInput_58(remainData, remainSize);
        case 40:
            return LLVMFuzzerTestOneInput_59(remainData, remainSize);
        case 41:
            return LLVMFuzzerTestOneInput_60(remainData, remainSize);
        case 42:
            return LLVMFuzzerTestOneInput_61(remainData, remainSize);
        case 43:
            return LLVMFuzzerTestOneInput_62(remainData, remainSize);
        case 44:
            return LLVMFuzzerTestOneInput_63(remainData, remainSize);
        case 45:
            return LLVMFuzzerTestOneInput_64(remainData, remainSize);
        case 46:
            return LLVMFuzzerTestOneInput_66(remainData, remainSize);
        case 47:
            return LLVMFuzzerTestOneInput_67(remainData, remainSize);
        case 48:
            return LLVMFuzzerTestOneInput_69(remainData, remainSize);
        case 49:
            return LLVMFuzzerTestOneInput_70(remainData, remainSize);
        case 50:
            return LLVMFuzzerTestOneInput_72(remainData, remainSize);
        case 51:
            return LLVMFuzzerTestOneInput_75(remainData, remainSize);
        case 52:
            return LLVMFuzzerTestOneInput_77(remainData, remainSize);
        case 53:
            return LLVMFuzzerTestOneInput_78(remainData, remainSize);
        case 54:
            return LLVMFuzzerTestOneInput_79(remainData, remainSize);
        case 55:
            return LLVMFuzzerTestOneInput_82(remainData, remainSize);
        case 56:
            return LLVMFuzzerTestOneInput_84(remainData, remainSize);
        case 57:
            return LLVMFuzzerTestOneInput_88(remainData, remainSize);
        case 58:
            return LLVMFuzzerTestOneInput_89(remainData, remainSize);
        case 59:
            return LLVMFuzzerTestOneInput_90(remainData, remainSize);
        case 60:
            return LLVMFuzzerTestOneInput_91(remainData, remainSize);
        case 61:
            return LLVMFuzzerTestOneInput_93(remainData, remainSize);
        case 62:
            return LLVMFuzzerTestOneInput_94(remainData, remainSize);
        case 63:
            return LLVMFuzzerTestOneInput_103(remainData, remainSize);
        case 64:
            return LLVMFuzzerTestOneInput_105(remainData, remainSize);
        case 65:
            return LLVMFuzzerTestOneInput_108(remainData, remainSize);
        case 66:
            return LLVMFuzzerTestOneInput_109(remainData, remainSize);
        case 67:
            return LLVMFuzzerTestOneInput_115(remainData, remainSize);
        default:
            return 0;
    }
    return 0;
}

int main(int argc, char *argv[])
{
	FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size+1);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);
    data[size] = '\0';

    LLVMFuzzerTestOneInput(data, size);

    free(data);
    fclose(f);
    return 0;
}

