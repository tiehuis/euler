const std = @import("std");

fn run() -> u32 {
    var i = u32(0);
    var sum = u32(0);
    while (i < 1000) : (i += 1) {
        if (i % 3 == 0) {
            sum += i;
        }
        if (i % 5 == 0) {
            sum += i;
        }
        if (i % 15 == 0) {
            sum -= i;
        }
    }
    sum
}

pub fn main() -> %void {
    const sum = comptime run();
    %%std.io.stdout.printf("{}\n", sum);
}

test "001" {
    std.debug.assert(run() == 233168);
}
