#include "../libcw/src/bootstrap.h"
#define LIBCW_ROOT "../libcw"

int main() {
    CwHost host = {0};
    if (cwhost_init(&host)) return 1;

    cw.a = cwarena_create(host.alloc, 1 << 14);
    cwlogger_init(&cw.log, cwarena_reserve(&cw.a, 1 << 8), host.get_stdout());

    CwBuilder build = {0};
    build.root = LIBCW_ROOT;
    build.dest = "build/libcw";

    cwbuilder_init(&build, cw, &host);
    libcw_bootstrap(&build, LIBCW_HOST_NATIVE, NULL);

    build.root = ".";
    build.dest = "build";

    char* objects_memory[16];
    CwList objects = cwlist_begin(cwtypeof(char*), cwarena(objects_memory));

    char* flags[] = { "-I" LIBCW_ROOT "/include" };
    build.flags = cwlist_from_array(flags);

    cwbuild_object(&build, &objects, "src/day01.c");
    cwbuild_object(&build, &objects, "src/main.c");

	const char* libs[] = { "-Lbuild/libcw", "-lcw", "-lm" };
    cwbuild_executable(&build, objects, cwlist_from_array(libs), "build/run");

	CwCmd cmd = cwcmd_create(cw.a, "build/run");
    host.process.spawn(cmd, (CwProcessOpts){0});

    return 0;
}
