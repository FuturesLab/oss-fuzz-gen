// This is the entry of 21 fuzz drivers:
// 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 40, 41, 42, 43, 44, 45, 46, 47, 48, 
// 51
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <memory.h>

// Declarations of all fuzz drivers `LLVMFuzzerTestOneInput` functions
int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size);

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
    switch (driverIndex % 21) {
        case 0:
            return LLVMFuzzerTestOneInput_28(remainData, remainSize);
        case 1:
            return LLVMFuzzerTestOneInput_29(remainData, remainSize);
        case 2:
            return LLVMFuzzerTestOneInput_30(remainData, remainSize);
        case 3:
            return LLVMFuzzerTestOneInput_31(remainData, remainSize);
        case 4:
            return LLVMFuzzerTestOneInput_32(remainData, remainSize);
        case 5:
            return LLVMFuzzerTestOneInput_33(remainData, remainSize);
        case 6:
            return LLVMFuzzerTestOneInput_34(remainData, remainSize);
        case 7:
            return LLVMFuzzerTestOneInput_35(remainData, remainSize);
        case 8:
            return LLVMFuzzerTestOneInput_36(remainData, remainSize);
        case 9:
            return LLVMFuzzerTestOneInput_37(remainData, remainSize);
        case 10:
            return LLVMFuzzerTestOneInput_38(remainData, remainSize);
        case 11:
            return LLVMFuzzerTestOneInput_40(remainData, remainSize);
        case 12:
            return LLVMFuzzerTestOneInput_41(remainData, remainSize);
        case 13:
            return LLVMFuzzerTestOneInput_42(remainData, remainSize);
        case 14:
            return LLVMFuzzerTestOneInput_43(remainData, remainSize);
        case 15:
            return LLVMFuzzerTestOneInput_44(remainData, remainSize);
        case 16:
            return LLVMFuzzerTestOneInput_45(remainData, remainSize);
        case 17:
            return LLVMFuzzerTestOneInput_46(remainData, remainSize);
        case 18:
            return LLVMFuzzerTestOneInput_47(remainData, remainSize);
        case 19:
            return LLVMFuzzerTestOneInput_48(remainData, remainSize);
        case 20:
            return LLVMFuzzerTestOneInput_51(remainData, remainSize);
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

