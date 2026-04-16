// This is the entry of 188 fuzz drivers:
// 2, 18, 19, 23, 25, 35, 36, 41, 42, 43, 44, 47, 50, 52, 61, 62, 64, 67, 73, 83, 8
// 4, 85, 88, 90, 95, 96, 101, 102, 103, 104, 116, 119, 124, 130, 131, 135, 137, 14
// 0, 141, 143, 146, 147, 150, 155, 165, 166, 168, 173, 199, 201, 205, 216, 223, 23
// 1, 236, 238, 252, 254, 258, 269, 278, 284, 290, 293, 295, 307, 309, 313, 317, 31
// 9, 327, 331, 335, 338, 344, 348, 353, 354, 364, 365, 373, 381, 397, 399, 404, 41
// 2, 417, 423, 425, 426, 427, 442, 448, 454, 459, 460, 463, 470, 471, 479, 480, 48
// 1, 482, 484, 485, 489, 493, 494, 496, 497, 498, 499, 500, 507, 508, 518, 524, 52
// 7, 528, 531, 533, 535, 541, 542, 546, 551, 557, 558, 566, 572, 573, 574, 579, 58
// 2, 583, 585, 587, 589, 596, 606, 616, 624, 625, 626, 635, 637, 639, 640, 644, 64
// 6, 653, 656, 658, 659, 661, 662, 663, 665, 668, 673, 680, 681, 684, 686, 687, 69
// 2, 701, 704, 713, 716, 723, 736, 740, 741, 745, 747, 753, 754, 768, 769, 770, 77
// 2, 785, 789, 792, 793, 794, 796
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <memory.h>

// Declarations of all fuzz drivers `LLVMFuzzerTestOneInput` functions
int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_73(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_83(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_88(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_95(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_101(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_102(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_104(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_116(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_119(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_124(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_130(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_131(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_135(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_137(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_140(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_141(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_143(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_146(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_147(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_150(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_155(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_165(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_166(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_168(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_173(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_199(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_201(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_205(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_216(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_223(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_231(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_236(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_238(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_252(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_254(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_258(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_269(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_278(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_284(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_290(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_293(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_295(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_307(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_309(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_313(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_317(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_319(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_327(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_331(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_335(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_338(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_344(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_348(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_353(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_354(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_364(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_365(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_373(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_381(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_397(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_399(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_404(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_412(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_417(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_423(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_425(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_426(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_427(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_442(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_448(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_454(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_459(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_460(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_463(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_470(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_471(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_479(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_480(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_481(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_482(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_484(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_485(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_489(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_493(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_494(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_496(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_497(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_498(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_499(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_500(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_507(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_508(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_518(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_524(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_527(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_528(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_531(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_533(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_535(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_541(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_542(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_546(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_551(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_557(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_558(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_566(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_572(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_573(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_574(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_579(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_582(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_583(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_585(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_587(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_589(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_596(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_606(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_616(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_624(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_625(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_626(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_635(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_637(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_639(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_640(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_644(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_646(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_653(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_656(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_658(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_659(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_661(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_662(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_663(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_665(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_668(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_673(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_680(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_681(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_684(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_686(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_687(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_692(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_701(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_704(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_713(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_716(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_723(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_736(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_740(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_741(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_745(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_747(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_753(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_754(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_768(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_769(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_770(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_772(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_785(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_789(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_792(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_793(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_794(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_796(const uint8_t *Data, size_t Size);

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
    switch (driverIndex % 188) {
        case 0:
            return LLVMFuzzerTestOneInput_2(remainData, remainSize);
        case 1:
            return LLVMFuzzerTestOneInput_18(remainData, remainSize);
        case 2:
            return LLVMFuzzerTestOneInput_19(remainData, remainSize);
        case 3:
            return LLVMFuzzerTestOneInput_23(remainData, remainSize);
        case 4:
            return LLVMFuzzerTestOneInput_25(remainData, remainSize);
        case 5:
            return LLVMFuzzerTestOneInput_35(remainData, remainSize);
        case 6:
            return LLVMFuzzerTestOneInput_36(remainData, remainSize);
        case 7:
            return LLVMFuzzerTestOneInput_41(remainData, remainSize);
        case 8:
            return LLVMFuzzerTestOneInput_42(remainData, remainSize);
        case 9:
            return LLVMFuzzerTestOneInput_43(remainData, remainSize);
        case 10:
            return LLVMFuzzerTestOneInput_44(remainData, remainSize);
        case 11:
            return LLVMFuzzerTestOneInput_47(remainData, remainSize);
        case 12:
            return LLVMFuzzerTestOneInput_50(remainData, remainSize);
        case 13:
            return LLVMFuzzerTestOneInput_52(remainData, remainSize);
        case 14:
            return LLVMFuzzerTestOneInput_61(remainData, remainSize);
        case 15:
            return LLVMFuzzerTestOneInput_62(remainData, remainSize);
        case 16:
            return LLVMFuzzerTestOneInput_64(remainData, remainSize);
        case 17:
            return LLVMFuzzerTestOneInput_67(remainData, remainSize);
        case 18:
            return LLVMFuzzerTestOneInput_73(remainData, remainSize);
        case 19:
            return LLVMFuzzerTestOneInput_83(remainData, remainSize);
        case 20:
            return LLVMFuzzerTestOneInput_84(remainData, remainSize);
        case 21:
            return LLVMFuzzerTestOneInput_85(remainData, remainSize);
        case 22:
            return LLVMFuzzerTestOneInput_88(remainData, remainSize);
        case 23:
            return LLVMFuzzerTestOneInput_90(remainData, remainSize);
        case 24:
            return LLVMFuzzerTestOneInput_95(remainData, remainSize);
        case 25:
            return LLVMFuzzerTestOneInput_96(remainData, remainSize);
        case 26:
            return LLVMFuzzerTestOneInput_101(remainData, remainSize);
        case 27:
            return LLVMFuzzerTestOneInput_102(remainData, remainSize);
        case 28:
            return LLVMFuzzerTestOneInput_103(remainData, remainSize);
        case 29:
            return LLVMFuzzerTestOneInput_104(remainData, remainSize);
        case 30:
            return LLVMFuzzerTestOneInput_116(remainData, remainSize);
        case 31:
            return LLVMFuzzerTestOneInput_119(remainData, remainSize);
        case 32:
            return LLVMFuzzerTestOneInput_124(remainData, remainSize);
        case 33:
            return LLVMFuzzerTestOneInput_130(remainData, remainSize);
        case 34:
            return LLVMFuzzerTestOneInput_131(remainData, remainSize);
        case 35:
            return LLVMFuzzerTestOneInput_135(remainData, remainSize);
        case 36:
            return LLVMFuzzerTestOneInput_137(remainData, remainSize);
        case 37:
            return LLVMFuzzerTestOneInput_140(remainData, remainSize);
        case 38:
            return LLVMFuzzerTestOneInput_141(remainData, remainSize);
        case 39:
            return LLVMFuzzerTestOneInput_143(remainData, remainSize);
        case 40:
            return LLVMFuzzerTestOneInput_146(remainData, remainSize);
        case 41:
            return LLVMFuzzerTestOneInput_147(remainData, remainSize);
        case 42:
            return LLVMFuzzerTestOneInput_150(remainData, remainSize);
        case 43:
            return LLVMFuzzerTestOneInput_155(remainData, remainSize);
        case 44:
            return LLVMFuzzerTestOneInput_165(remainData, remainSize);
        case 45:
            return LLVMFuzzerTestOneInput_166(remainData, remainSize);
        case 46:
            return LLVMFuzzerTestOneInput_168(remainData, remainSize);
        case 47:
            return LLVMFuzzerTestOneInput_173(remainData, remainSize);
        case 48:
            return LLVMFuzzerTestOneInput_199(remainData, remainSize);
        case 49:
            return LLVMFuzzerTestOneInput_201(remainData, remainSize);
        case 50:
            return LLVMFuzzerTestOneInput_205(remainData, remainSize);
        case 51:
            return LLVMFuzzerTestOneInput_216(remainData, remainSize);
        case 52:
            return LLVMFuzzerTestOneInput_223(remainData, remainSize);
        case 53:
            return LLVMFuzzerTestOneInput_231(remainData, remainSize);
        case 54:
            return LLVMFuzzerTestOneInput_236(remainData, remainSize);
        case 55:
            return LLVMFuzzerTestOneInput_238(remainData, remainSize);
        case 56:
            return LLVMFuzzerTestOneInput_252(remainData, remainSize);
        case 57:
            return LLVMFuzzerTestOneInput_254(remainData, remainSize);
        case 58:
            return LLVMFuzzerTestOneInput_258(remainData, remainSize);
        case 59:
            return LLVMFuzzerTestOneInput_269(remainData, remainSize);
        case 60:
            return LLVMFuzzerTestOneInput_278(remainData, remainSize);
        case 61:
            return LLVMFuzzerTestOneInput_284(remainData, remainSize);
        case 62:
            return LLVMFuzzerTestOneInput_290(remainData, remainSize);
        case 63:
            return LLVMFuzzerTestOneInput_293(remainData, remainSize);
        case 64:
            return LLVMFuzzerTestOneInput_295(remainData, remainSize);
        case 65:
            return LLVMFuzzerTestOneInput_307(remainData, remainSize);
        case 66:
            return LLVMFuzzerTestOneInput_309(remainData, remainSize);
        case 67:
            return LLVMFuzzerTestOneInput_313(remainData, remainSize);
        case 68:
            return LLVMFuzzerTestOneInput_317(remainData, remainSize);
        case 69:
            return LLVMFuzzerTestOneInput_319(remainData, remainSize);
        case 70:
            return LLVMFuzzerTestOneInput_327(remainData, remainSize);
        case 71:
            return LLVMFuzzerTestOneInput_331(remainData, remainSize);
        case 72:
            return LLVMFuzzerTestOneInput_335(remainData, remainSize);
        case 73:
            return LLVMFuzzerTestOneInput_338(remainData, remainSize);
        case 74:
            return LLVMFuzzerTestOneInput_344(remainData, remainSize);
        case 75:
            return LLVMFuzzerTestOneInput_348(remainData, remainSize);
        case 76:
            return LLVMFuzzerTestOneInput_353(remainData, remainSize);
        case 77:
            return LLVMFuzzerTestOneInput_354(remainData, remainSize);
        case 78:
            return LLVMFuzzerTestOneInput_364(remainData, remainSize);
        case 79:
            return LLVMFuzzerTestOneInput_365(remainData, remainSize);
        case 80:
            return LLVMFuzzerTestOneInput_373(remainData, remainSize);
        case 81:
            return LLVMFuzzerTestOneInput_381(remainData, remainSize);
        case 82:
            return LLVMFuzzerTestOneInput_397(remainData, remainSize);
        case 83:
            return LLVMFuzzerTestOneInput_399(remainData, remainSize);
        case 84:
            return LLVMFuzzerTestOneInput_404(remainData, remainSize);
        case 85:
            return LLVMFuzzerTestOneInput_412(remainData, remainSize);
        case 86:
            return LLVMFuzzerTestOneInput_417(remainData, remainSize);
        case 87:
            return LLVMFuzzerTestOneInput_423(remainData, remainSize);
        case 88:
            return LLVMFuzzerTestOneInput_425(remainData, remainSize);
        case 89:
            return LLVMFuzzerTestOneInput_426(remainData, remainSize);
        case 90:
            return LLVMFuzzerTestOneInput_427(remainData, remainSize);
        case 91:
            return LLVMFuzzerTestOneInput_442(remainData, remainSize);
        case 92:
            return LLVMFuzzerTestOneInput_448(remainData, remainSize);
        case 93:
            return LLVMFuzzerTestOneInput_454(remainData, remainSize);
        case 94:
            return LLVMFuzzerTestOneInput_459(remainData, remainSize);
        case 95:
            return LLVMFuzzerTestOneInput_460(remainData, remainSize);
        case 96:
            return LLVMFuzzerTestOneInput_463(remainData, remainSize);
        case 97:
            return LLVMFuzzerTestOneInput_470(remainData, remainSize);
        case 98:
            return LLVMFuzzerTestOneInput_471(remainData, remainSize);
        case 99:
            return LLVMFuzzerTestOneInput_479(remainData, remainSize);
        case 100:
            return LLVMFuzzerTestOneInput_480(remainData, remainSize);
        case 101:
            return LLVMFuzzerTestOneInput_481(remainData, remainSize);
        case 102:
            return LLVMFuzzerTestOneInput_482(remainData, remainSize);
        case 103:
            return LLVMFuzzerTestOneInput_484(remainData, remainSize);
        case 104:
            return LLVMFuzzerTestOneInput_485(remainData, remainSize);
        case 105:
            return LLVMFuzzerTestOneInput_489(remainData, remainSize);
        case 106:
            return LLVMFuzzerTestOneInput_493(remainData, remainSize);
        case 107:
            return LLVMFuzzerTestOneInput_494(remainData, remainSize);
        case 108:
            return LLVMFuzzerTestOneInput_496(remainData, remainSize);
        case 109:
            return LLVMFuzzerTestOneInput_497(remainData, remainSize);
        case 110:
            return LLVMFuzzerTestOneInput_498(remainData, remainSize);
        case 111:
            return LLVMFuzzerTestOneInput_499(remainData, remainSize);
        case 112:
            return LLVMFuzzerTestOneInput_500(remainData, remainSize);
        case 113:
            return LLVMFuzzerTestOneInput_507(remainData, remainSize);
        case 114:
            return LLVMFuzzerTestOneInput_508(remainData, remainSize);
        case 115:
            return LLVMFuzzerTestOneInput_518(remainData, remainSize);
        case 116:
            return LLVMFuzzerTestOneInput_524(remainData, remainSize);
        case 117:
            return LLVMFuzzerTestOneInput_527(remainData, remainSize);
        case 118:
            return LLVMFuzzerTestOneInput_528(remainData, remainSize);
        case 119:
            return LLVMFuzzerTestOneInput_531(remainData, remainSize);
        case 120:
            return LLVMFuzzerTestOneInput_533(remainData, remainSize);
        case 121:
            return LLVMFuzzerTestOneInput_535(remainData, remainSize);
        case 122:
            return LLVMFuzzerTestOneInput_541(remainData, remainSize);
        case 123:
            return LLVMFuzzerTestOneInput_542(remainData, remainSize);
        case 124:
            return LLVMFuzzerTestOneInput_546(remainData, remainSize);
        case 125:
            return LLVMFuzzerTestOneInput_551(remainData, remainSize);
        case 126:
            return LLVMFuzzerTestOneInput_557(remainData, remainSize);
        case 127:
            return LLVMFuzzerTestOneInput_558(remainData, remainSize);
        case 128:
            return LLVMFuzzerTestOneInput_566(remainData, remainSize);
        case 129:
            return LLVMFuzzerTestOneInput_572(remainData, remainSize);
        case 130:
            return LLVMFuzzerTestOneInput_573(remainData, remainSize);
        case 131:
            return LLVMFuzzerTestOneInput_574(remainData, remainSize);
        case 132:
            return LLVMFuzzerTestOneInput_579(remainData, remainSize);
        case 133:
            return LLVMFuzzerTestOneInput_582(remainData, remainSize);
        case 134:
            return LLVMFuzzerTestOneInput_583(remainData, remainSize);
        case 135:
            return LLVMFuzzerTestOneInput_585(remainData, remainSize);
        case 136:
            return LLVMFuzzerTestOneInput_587(remainData, remainSize);
        case 137:
            return LLVMFuzzerTestOneInput_589(remainData, remainSize);
        case 138:
            return LLVMFuzzerTestOneInput_596(remainData, remainSize);
        case 139:
            return LLVMFuzzerTestOneInput_606(remainData, remainSize);
        case 140:
            return LLVMFuzzerTestOneInput_616(remainData, remainSize);
        case 141:
            return LLVMFuzzerTestOneInput_624(remainData, remainSize);
        case 142:
            return LLVMFuzzerTestOneInput_625(remainData, remainSize);
        case 143:
            return LLVMFuzzerTestOneInput_626(remainData, remainSize);
        case 144:
            return LLVMFuzzerTestOneInput_635(remainData, remainSize);
        case 145:
            return LLVMFuzzerTestOneInput_637(remainData, remainSize);
        case 146:
            return LLVMFuzzerTestOneInput_639(remainData, remainSize);
        case 147:
            return LLVMFuzzerTestOneInput_640(remainData, remainSize);
        case 148:
            return LLVMFuzzerTestOneInput_644(remainData, remainSize);
        case 149:
            return LLVMFuzzerTestOneInput_646(remainData, remainSize);
        case 150:
            return LLVMFuzzerTestOneInput_653(remainData, remainSize);
        case 151:
            return LLVMFuzzerTestOneInput_656(remainData, remainSize);
        case 152:
            return LLVMFuzzerTestOneInput_658(remainData, remainSize);
        case 153:
            return LLVMFuzzerTestOneInput_659(remainData, remainSize);
        case 154:
            return LLVMFuzzerTestOneInput_661(remainData, remainSize);
        case 155:
            return LLVMFuzzerTestOneInput_662(remainData, remainSize);
        case 156:
            return LLVMFuzzerTestOneInput_663(remainData, remainSize);
        case 157:
            return LLVMFuzzerTestOneInput_665(remainData, remainSize);
        case 158:
            return LLVMFuzzerTestOneInput_668(remainData, remainSize);
        case 159:
            return LLVMFuzzerTestOneInput_673(remainData, remainSize);
        case 160:
            return LLVMFuzzerTestOneInput_680(remainData, remainSize);
        case 161:
            return LLVMFuzzerTestOneInput_681(remainData, remainSize);
        case 162:
            return LLVMFuzzerTestOneInput_684(remainData, remainSize);
        case 163:
            return LLVMFuzzerTestOneInput_686(remainData, remainSize);
        case 164:
            return LLVMFuzzerTestOneInput_687(remainData, remainSize);
        case 165:
            return LLVMFuzzerTestOneInput_692(remainData, remainSize);
        case 166:
            return LLVMFuzzerTestOneInput_701(remainData, remainSize);
        case 167:
            return LLVMFuzzerTestOneInput_704(remainData, remainSize);
        case 168:
            return LLVMFuzzerTestOneInput_713(remainData, remainSize);
        case 169:
            return LLVMFuzzerTestOneInput_716(remainData, remainSize);
        case 170:
            return LLVMFuzzerTestOneInput_723(remainData, remainSize);
        case 171:
            return LLVMFuzzerTestOneInput_736(remainData, remainSize);
        case 172:
            return LLVMFuzzerTestOneInput_740(remainData, remainSize);
        case 173:
            return LLVMFuzzerTestOneInput_741(remainData, remainSize);
        case 174:
            return LLVMFuzzerTestOneInput_745(remainData, remainSize);
        case 175:
            return LLVMFuzzerTestOneInput_747(remainData, remainSize);
        case 176:
            return LLVMFuzzerTestOneInput_753(remainData, remainSize);
        case 177:
            return LLVMFuzzerTestOneInput_754(remainData, remainSize);
        case 178:
            return LLVMFuzzerTestOneInput_768(remainData, remainSize);
        case 179:
            return LLVMFuzzerTestOneInput_769(remainData, remainSize);
        case 180:
            return LLVMFuzzerTestOneInput_770(remainData, remainSize);
        case 181:
            return LLVMFuzzerTestOneInput_772(remainData, remainSize);
        case 182:
            return LLVMFuzzerTestOneInput_785(remainData, remainSize);
        case 183:
            return LLVMFuzzerTestOneInput_789(remainData, remainSize);
        case 184:
            return LLVMFuzzerTestOneInput_792(remainData, remainSize);
        case 185:
            return LLVMFuzzerTestOneInput_793(remainData, remainSize);
        case 186:
            return LLVMFuzzerTestOneInput_794(remainData, remainSize);
        case 187:
            return LLVMFuzzerTestOneInput_796(remainData, remainSize);
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

