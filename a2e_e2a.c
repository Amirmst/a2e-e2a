#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define ERROR -1 // Causes a lossy conversion.

int error_message();
int a2e_func(FILE *stream);
int e2a_func(FILE *stream);
bool is_well_formed_set(set_t set);
bool posittiond_right(int xl, int yl, int xh, int yh);
bool overlap(int x1l, int y1l, int x1h, int y1h, int x2l, int y2l, int x2h, int y2h);

static const unsigned char e2a[256] = {
    0, 
    1,  
    2,  
    3,
    ERROR,  
    9,
    ERROR,
    127,
    ERROR,
    ERROR,
    ERROR, 
    11, 
    12, 
    13, 
    14, 
    15,
    16, 
    17, 
    18, 
    19,
    ERROR,
    ERROR,  
    8,
    ERROR, 
    24, 
    25,
    ERROR,
    ERROR, 
    28, 
    29, 
    30, 
    31,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR, 
    10, 
    23, 
    27,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,  
    5,  
    6,  
    7,
    ERROR,
    ERROR, 
    22,
    ERROR,
    ERROR,
    ERROR,
    ERROR,  
    4,
    ERROR,
    ERROR,
    ERROR,
    ERROR, 
    20, 
    21,
    ERROR, 
    26,
    32,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR, 
    91, 
    46, 
    60, 
    40, 
    43, 
    33,
    38,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR, 
    93, 
    36, 
    42, 
    41, 
    59, 
    94,
    45, 
    47,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    124, 
    44, 
    37, 
    95, 
    62, 
    63,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR, 
    96, 
    58, 
    35, 
    64, 
    39, 
    61, 
    34,
    ERROR, 
    97, 
    98, 
    99,
    100,
    101,
    102,
    103,
    104,
    105,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    106,
    107,
    108,
    109,
    110,
    111,
    112,
    113,
    114,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    126,
    115,
    116,
    117,
    118,
    119,
    120,
    121,
    122,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    123, 
    65, 
    66, 
    67, 
    68, 
    69, 
    70, 
    71, 
    72, 
    73,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    125, 
    74, 
    75, 
    76, 
    77, 
    78, 
    79, 
    80, 
    81, 
    82,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    92,
    ERROR, 
    83, 
    84, 
    85, 
    86, 
    87, 
    88, 
    89, 
    90,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    48, 
    49, 
    50, 
    51, 
    52, 
    53, 
    54, 
    55, 
    56, 
    57,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
    ERROR,
	ERROR
};

static const unsigned int a2e[128] = {
	0,
	1,
	2,
	3,
	55,
	45,
	46,
	47,
	22,
	5,
	37,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	60,
	61,
	50,
	38,
	24,
	25,
	63,
	39,
	28,
	29,
	30,
	31,
	64,
	79,
	127,
	123,
	91,
	108,
	80,
	125,
	77,
	93,
	92,
	78,
	107,
	96,
	75,
	97,
	240,
	241,
	242,
	243,
	244,
	245,
	246,
	247,
	248,
	249,
	122,
	94,
	76,
	126,
	110,
	111,
	124,
	193,
	194,
	195,
	196,
	197,
	198,
	199,
	200,
	201,
	209,
	210,
	211,
	212,
	213,
	214,
	215,
	216,
	217,
	226,
	227,
	228,
	229,
	230,
	231,
	232,
	233,
	74,
	224,
	90,
	95,
	109,
	121,
	129,
	130,
	131,
	132,
	133,
	134,
	135,
	136,
	137,
	145,
	146,
	147,
	148,
	149,
	150,
	151,
	152,
	153,
	162,
	163,
	164,
	165,
	166,
	167,
	168,
	169,
	192,
	106,
	208,
	161,
	7
};

int main(int argc, char *argv[]) {
    if(argc != 2) {
        // ERROR
        return error_message();
    }
    if(strcmp (argv[1], "a2e") == 0) {
        // a2e
        //printf("a2e\n");
        return a2e_func(stdin);
    } else if(strcmp (argv[1], "e2a") == 0) {
        // e2a
        return e2a_func(stdin);
    } else {
        // ERROR
        return error_message();
    }
    return 0;
}

int error_message() {
    printf("Please enter 1 and only 1 command line argument\n(i) a2e for ASCII to EBCDIC\n(ii) e2a for EBCDIC to ASCII\n");
    exit(-1);
    return -1;
}

int a2e_func(FILE *stream) {
    /* Lossy cases happen when ASCII is:
       1. '^'
       2. '['
       3. ']'
    */
    int ret_val = 0;
    int c;
    c = getc(stream);
    while(c != EOF) {
        if(c == '^' || c == '[' || c == ']') {
            ret_val = -1;
        }
        int ebcdic = a2e[c];
        putc(ebcdic, stdout);
        c = getc(stream);
    }
    // Hmmm...? Something to do with EOF?
    printf("\n");
    return ret_val;
}

int e2a_func(FILE *stream) {
    int ret_val = 0;
    int c;
    c = getc(stream);
    while(c != EOF) {
        int ascii = e2a[c];
        if(ascii == ERROR) {
            ret_val = -1;
            if(c == 0x4A) {
                // cent
                ascii = 'c';
            } else if (c == 0x6A || c == 0xFA) {
                // vertical bar or line
                ascii = '|';
            } else if (c == 0x5F) {
                // logical not
                ascii = '~';
            } else {
                // business decision... put a space character!
            	ascii = ' ';
            }
        }
        putc(ascii, stdout);
        c = getc(stream);
    }
    printf("\n");
    return ret_val;
}