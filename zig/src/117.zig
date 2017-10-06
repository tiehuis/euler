const std = @import("std");

fn run(comptime T: type, comptime N: usize) -> T {
    var row: [N + 1]T = undefined;
    row[0] = 1;

    var n: usize = 1;
    while (n <= N): (n += 1) {
        var k: usize = 1;
        while (k <= 4 and k <= n) : (k += 1) {
            row[n] += row[n - k];
        }
    }

    row[N]
}

pub fn main() -> %void {
    const sum = run(u64, 50);
    %%std.io.stdout.printf("{}\n", sum);
}

test "117" {
    std.debug.assert(run(u64, 50) == 100808458960497);
}
