#include <cwcore.h>
#include <cwhost.h>

typedef CwStr (Solution)(CwStr input, int part);

Solution day01;

char* example = "L68\nL30\nR48\nL5\nR60\nL55\nL1\nL99\nR14\nL82";

int main() {
    CwHost host = {0};
    if (cwhost_init(&host)) return 1;


	cw.a = cwarena_create(host.alloc, 1 << 20);
    cwlogger_init(&cw.log, cwarena_reserve(&cw.a, 1 << 8), host.get_stdout());

    CwStr input = host.fs.read_all(&cw.a, "input/day01.txt");
    // CwStr output = day01(input, 1);

    cwlog("day 01 A: %w - expected 1182", day01(input, 1));
    cwlog("day 01 B: %w - expected 6907", day01(input, 2));

    // day_01B(cw, cwstr(example));

	return 0;
}
