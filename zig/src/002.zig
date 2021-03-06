const debug = @import("std").debug;

fn run() u32 {
    var f1 = u32(1);
    var f2 = u32(2);
    var fs = u32(0);

    while (f1 < 4000000) {
        if (f1 % 2 == 0) {
            fs += f1;
        }

        f2 += f1;
        f1 = f2 - f1;
    }

    return fs;
}

pub fn main() !void {
    const sum = comptime run();
    try debug.warn("{}\n", sum);
}

test "002" {
    debug.assert(run() == 4613732);
}
