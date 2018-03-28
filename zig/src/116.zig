const debug = @import("std").debug;

fn r(comptime T: type, comptime N: usize, comptime L: usize) T {
    var row: [N + 1]T = []T{0} ** (N + 1);
    row[0] = 1;

    var n: usize = 1;
    while (n <= N) : (n += 1) {
        row[n] += row[n - 1];
        if (L <= n) {
            row[n] += row[n - L];
        }
    }

    // exclude the empty set
    return row[N] - 1;
}

fn run(comptime T: type, comptime N: usize) T {
    return r(T, N, 2) + r(T, N, 3) + r(T, N, 4);
}

pub fn main() void {
    const sum = run(u64, 50);
    debug.warn("{}\n", sum);
}

test "116" {
    debug.assert(run(u64, 50) == 20492570929);
}
