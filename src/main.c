#include <cwcore.h>
#include <cwhost.h>


typedef CwStr (Solution)(CwStr input, int part);

Solution day01;
Solution day02;
Solution day03;

CwHost host = {0};

CwStr load(CwArena a, const char* path) {
    return host.fs.read_all(&a, path);
}

int main() {
    if (cwhost_init(&host)) return 1;

	cw.a = cwarena_create(host.alloc, 1 << 20);
    cwlogger_init(&cw.log, cwarena_reserve(&cw.a, 1 << 8), host.get_stdout());

    CwArena input_memory = cwarena_create(host.alloc, 1 << 20);
    CwStr input;

	input = load(input_memory, "input/day01.txt");
    cwlog("day 01 A: %w - expected 1182", day01(input, 1));
    cwlog("day 01 B: %w - expected 6907", day01(input, 2));

	input = load(input_memory, "input/day02.txt");
    cwlog("day 02 A: %w - expected 41294979841", day02(input, 1));
    cwlog("day 02 B: %w - expected 66500947346", day02(input, 2));

	input = load(input_memory, "input/day03.txt");
    cwlog("day 03 A: %w - expected 17281", day03(input, 1));
    cwlog("day 03 B: %w - expected 171388730430281", day03(input, 2));

	return 0;
}
