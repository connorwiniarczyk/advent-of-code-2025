#include <cwcore.h>
#include <cwhost.h>

static char* example = "L68\nL30\nR48\nL5\nR60\nL55\nL1\nL99\nR14\nL82";

typedef struct Dial {
    int value;
    int output;
    int part;
} Dial;

void dial_rotate_left(Dial* dial, int amount) {
	while (amount > 0) {
		amount -= 1;
		dial -> value -= 1;

		if (dial -> part == 2 && dial -> value == 0) {
    		dial -> output += 1;
		}

		if (dial -> value < 0) {
    		dial -> value += 100;
		}
	}

	if (dial -> part == 1 && dial -> value == 0) {
		dial -> output += 1;
	}
}

void dial_rotate_right(Dial* dial, int amount) {
	while (amount > 0) {
		amount -= 1;
		dial -> value += 1;

		if (dial -> part == 2 && dial -> value == 100) {
    		dial -> output += 1;
		}

		if (dial -> value >= 100) {
    		dial -> value  = 0;
		}

	}

	if (dial -> part == 1 && dial -> value == 0) {
		dial -> output += 1;
	}
}

CwStr day01(CwStr input, int part) {

    Dial dial = {0};
    dial.value = 50;
    dial.part = part;

    while (input.size) {
        CwStr next = cwstr_split(&input, '\n');
		if (next.size <= 0) continue;

		switch (next.ptr[0]) {
    		case 'R': dial_rotate_right(&dial, cwparse_int(cwstr_substr(next, 1, next.size))); break;
    		case 'L': dial_rotate_left(&dial, cwparse_int(cwstr_substr(next, 1, next.size))); break;
    		default: return cwstr("failed");
		}
    }

    return cwfmt(&cw.a, "%d", dial.output);
    (void)(example);
}
