// slow-ish brute-force solution.

const std = @import("std");

fn isAllOdd(nn: u64) -> bool {
    var n = nn;
    while (n != 0) : (n /= 10) {
        if ((n % 10) % 2 == 0) {
            return false;
        }
    }

    true
}

fn digitAt(n: u64, i: u64) -> u64 {
    (n / pow10(i)) % 10
}

fn isReversible(comptime digits: u64, n: u64) -> u64 {
    // filter out leading zero case
    if (n % 10 == 0) {
        return 0;
    }

    var sum = n;
    var i: u64 = 0;
    while (i <= digits) : (i += 1) {
        sum += digitAt(n, digits - i) * pow10(i);
    }

    if (isAllOdd(sum)) {
        u64(1)
    } else {
        0
    }
}

fn pow10(x: var) -> @typeOf(x) {
    var s: @typeOf(x) = 1;
    var i: usize = 0;
    while (i < x) : (i += 1) {
        s *= 10;
    }

    s
}

fn isReversibleRange(comptime digits: u64) -> u64 {
    const lo = pow10(digits);
    const hi = pow10(digits + 1);

    var sum: u64 = 0;
    var i: u64 = lo;
    while (i < hi) : (i += 1) {
        sum += isReversible(digits, i);
    }

    sum
}

fn run(comptime digits: u8) -> u64 {
    var sum: u64 = 0;

    comptime var i: u8 = 1;
    inline while (i < digits) : (i += 1) {
        sum += isReversibleRange(i);
    }

    sum
}

pub fn main() -> %void {
    const sum = run(9);
    %%std.io.stdout.printf("{}\n", sum);
}

test "145" {
    std.debug.assert(run(9) == 608720);
}
