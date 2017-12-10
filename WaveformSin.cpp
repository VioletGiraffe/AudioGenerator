#include "WaveformSin.h"

const uint16_t CWaveformSin::wavetable[] = {
	2048,
	2069,
	2091,
	2112,
	2134,
	2155,
	2177,
	2198,
	2219,
	2241,
	2262,
	2283,
	2305,
	2326,
	2347,
	2368,
	2390,
	2411,
	2432,
	2453,
	2474,
	2495,
	2516,
	2537,
	2557,
	2578,
	2599,
	2619,
	2640,
	2660,
	2681,
	2701,
	2722,
	2742,
	2762,
	2782,
	2802,
	2822,
	2842,
	2861,
	2881,
	2901,
	2920,
	2939,
	2959,
	2978,
	2997,
	3016,
	3035,
	3053,
	3072,
	3091,
	3109,
	3127,
	3145,
	3163,
	3181,
	3199,
	3217,
	3234,
	3252,
	3269,
	3286,
	3303,
	3320,
	3337,
	3353,
	3370,
	3386,
	3402,
	3418,
	3434,
	3450,
	3466,
	3481,
	3496,
	3511,
	3526,
	3541,
	3556,
	3570,
	3584,
	3598,
	3612,
	3626,
	3640,
	3653,
	3666,
	3679,
	3692,
	3705,
	3717,
	3730,
	3742,
	3754,
	3766,
	3777,
	3789,
	3800,
	3811,
	3822,
	3832,
	3843,
	3853,
	3863,
	3873,
	3882,
	3892,
	3901,
	3910,
	3919,
	3928,
	3936,
	3944,
	3952,
	3960,
	3968,
	3975,
	3982,
	3989,
	3996,
	4002,
	4009,
	4015,
	4021,
	4026,
	4032,
	4037,
	4042,
	4047,
	4051,
	4056,
	4060,
	4064,
	4067,
	4071,
	4074,
	4077,
	4080,
	4082,
	4085,
	4087,
	4089,
	4091,
	4092,
	4093,
	4094,
	4095,
	4096,
	4096,
	4096,
	4096,
	4096,
	4095,
	4094,
	4093,
	4092,
	4091,
	4089,
	4087,
	4085,
	4082,
	4080,
	4077,
	4074,
	4071,
	4067,
	4064,
	4060,
	4056,
	4051,
	4047,
	4042,
	4037,
	4032,
	4026,
	4021,
	4015,
	4009,
	4002,
	3996,
	3989,
	3982,
	3975,
	3968,
	3960,
	3952,
	3944,
	3936,
	3928,
	3919,
	3910,
	3901,
	3892,
	3882,
	3873,
	3863,
	3853,
	3843,
	3832,
	3822,
	3811,
	3800,
	3789,
	3777,
	3766,
	3754,
	3742,
	3730,
	3717,
	3705,
	3692,
	3679,
	3666,
	3653,
	3640,
	3626,
	3612,
	3598,
	3584,
	3570,
	3556,
	3541,
	3526,
	3511,
	3496,
	3481,
	3466,
	3450,
	3434,
	3418,
	3402,
	3386,
	3370,
	3353,
	3337,
	3320,
	3303,
	3286,
	3269,
	3252,
	3234,
	3217,
	3199,
	3181,
	3163,
	3145,
	3127,
	3109,
	3091,
	3072,
	3053,
	3035,
	3016,
	2997,
	2978,
	2959,
	2939,
	2920,
	2901,
	2881,
	2861,
	2842,
	2822,
	2802,
	2782,
	2762,
	2742,
	2722,
	2701,
	2681,
	2660,
	2640,
	2619,
	2599,
	2578,
	2557,
	2537,
	2516,
	2495,
	2474,
	2453,
	2432,
	2411,
	2390,
	2368,
	2347,
	2326,
	2305,
	2283,
	2262,
	2241,
	2219,
	2198,
	2177,
	2155,
	2134,
	2112,
	2091,
	2069,
	2048,
	2027,
	2005,
	1984,
	1962,
	1941,
	1919,
	1898,
	1877,
	1855,
	1834,
	1813,
	1791,
	1770,
	1749,
	1728,
	1706,
	1685,
	1664,
	1643,
	1622,
	1601,
	1580,
	1559,
	1539,
	1518,
	1497,
	1477,
	1456,
	1436,
	1415,
	1395,
	1374,
	1354,
	1334,
	1314,
	1294,
	1274,
	1254,
	1235,
	1215,
	1195,
	1176,
	1157,
	1137,
	1118,
	1099,
	1080,
	1061,
	1043,
	1024,
	1005,
	987,
	969,
	951,
	933,
	915,
	897,
	879,
	862,
	844,
	827,
	810,
	793,
	776,
	759,
	743,
	726,
	710,
	694,
	678,
	662,
	646,
	630,
	615,
	600,
	585,
	570,
	555,
	540,
	526,
	512,
	498,
	484,
	470,
	456,
	443,
	430,
	417,
	404,
	391,
	379,
	366,
	354,
	342,
	330,
	319,
	307,
	296,
	285,
	274,
	264,
	253,
	243,
	233,
	223,
	214,
	204,
	195,
	186,
	177,
	168,
	160,
	152,
	144,
	136,
	128,
	121,
	114,
	107,
	100,
	94,
	87,
	81,
	75,
	70,
	64,
	59,
	54,
	49,
	45,
	40,
	36,
	32,
	29,
	25,
	22,
	19,
	16,
	14,
	11,
	9,
	7,
	5,
	4,
	3,
	2,
	1,
	0,
	0,
	0,
	0,
	0,
	1,
	2,
	3,
	4,
	5,
	7,
	9,
	11,
	14,
	16,
	19,
	22,
	25,
	29,
	32,
	36,
	40,
	45,
	49,
	54,
	59,
	64,
	70,
	75,
	81,
	87,
	94,
	100,
	107,
	114,
	121,
	128,
	136,
	144,
	152,
	160,
	168,
	177,
	186,
	195,
	204,
	214,
	223,
	233,
	243,
	253,
	264,
	274,
	285,
	296,
	307,
	319,
	330,
	342,
	354,
	366,
	379,
	391,
	404,
	417,
	430,
	443,
	456,
	470,
	484,
	498,
	512,
	526,
	540,
	555,
	570,
	585,
	600,
	615,
	630,
	646,
	662,
	678,
	694,
	710,
	726,
	743,
	759,
	776,
	793,
	810,
	827,
	844,
	862,
	879,
	897,
	915,
	933,
	951,
	969,
	987,
	1005,
	1024,
	1043,
	1061,
	1080,
	1099,
	1118,
	1137,
	1157,
	1176,
	1195,
	1215,
	1235,
	1254,
	1274,
	1294,
	1314,
	1334,
	1354,
	1374,
	1395,
	1415,
	1436,
	1456,
	1477,
	1497,
	1518,
	1539,
	1559,
	1580,
	1601,
	1622,
	1643,
	1664,
	1685,
	1706,
	1728,
	1749,
	1770,
	1791,
	1813,
	1834,
	1855,
	1877,
	1898,
	1919,
	1941,
	1962,
	1984,
	2005,
	2027
};
