const debug = @import("std").debug;

fn run(comptime T: type, comptime N: usize) T {
    var row: [N + 1]T = []T{0} ** (N + 1);
    row[0] = 1;

    var n: usize = 1;
    while (n <= N): (n += 1) {
        var k: usize = 1;
        while (k <= 4 and k <= n) : (k += 1) {
            row[n] += row[n - k];
        }
    }

    return row[N];
}

pub fn main() void {
    const sum = run(u64, 50);
    debug.warn("{}\n", sum);
}

test "117" {
    debug.assert(run(u64, 50) == 100808458960497);
}
