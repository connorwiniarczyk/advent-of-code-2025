#include <cwcore.h>
#include <stdio.h>

#ifdef EXAMPLE
static const char* example = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124";
#endif

bool test_repeating(CwStr input, int window_size) {
    if (input.size % window_size != 0) {
        return false;
    }

	CwStr left = cwstr_substr(input, 0, window_size); 
	CwStr right = left;
	right.ptr += window_size;

	for (; (right.ptr + right.size <= input.ptr + input.size); right.ptr += window_size) {
    	if (!cwstr_equals(left, right)) {
			return false;
    	}
	}

	return true;
}

bool test_invalid_id(CwArena fmt, long int id, int part) {
    CwStr input = cwfmt_big_dec(&fmt, id, 0);

    if (part == 1) {
        int segments = 2;
        CwStr left = cwstr_substr(input, 0, input.size / segments);
        CwStr right = cwstr_substr(input, input.size / segments, input.size);
        return cwstr_equals(left, right);
    }

    if (part == 2) {
        for (int segments = 2; segments <= input.size; segments++) {
            int size = input.size / segments;
            if (test_repeating(input, size)) {
                return true;
            }
        }

        return false;
    }

    return false;
}

void find_invalid_ids(long int first, long int last, CwList* output, int part) {
    for (long int i=first; i<=last; i++) {
        if (test_invalid_id(cw.a, i, part)) {
            cwlist_push_write(output, long int, i);
        }
    }
}

CwStr day02(CwStr input, int part) {
    CwArena a = cw.a;
    #ifdef EXAMPLE
    input = cwstr(example);
    #endif

    long int memory[1 << 12];
    CwList invalid_ids = cwlist_begin(cwtypeof(long int), cwarena(memory));

    if (input.ptr[input.size - 1] == '\n') {
        input = cwstr_substr(input, 0, input.size - 1);
    }

    while (input.size) {
        CwStr last = cwstr_split(&input, ',');
        CwStr first = cwstr_split(&last, '-');

        find_invalid_ids(cwparse_int(first), cwparse_int(last), &invalid_ids, part);
    }

	int64_t sum = 0;
    for (long int* n; (n = cwlist_next(&invalid_ids));) {
        sum += *n;
    }

    return cwfmt_big_dec(&a, sum, 0);
}
