#include <cwcore.h>

#ifdef EXAMPLE
static char* example = "987654321111111\n811111111111119\n234234234234278\n818181911112111";
#endif

#define MAX_DIGITS 16
int64_t solve_row(CwStr row, int length) {
    char digits[MAX_DIGITS] = {0};
    char indeces[MAX_DIGITS] = {0};

	for (int i=0; i<length; i++) {
    	int j = i ? indeces[i - 1] + 1 : 0;
    	digits[i] = '0';
    	for (; j < row.size - (length - i - 1); j++) {
        	if (row.ptr[j] > digits[i]) {
            	digits[i] = row.ptr[j];
            	indeces[i] = j;
        	}
    	}
	}

	CwStr output = { digits, length };
	return cwparse_int(output);
}

CwStr day03(CwStr input, int part) {
    #ifdef EXAMPLE
    input = cwstr(example);
    #endif

    int64_t sum = 0;

    while (input.size) {
        CwStr bank = cwstr_split(&input, '\n');
        static int digits[] = { 0, 2, 12 };

        sum += solve_row(bank, digits[part]);
    }

	return cwfmt_big_dec(&cw.a, sum, 0);
}
