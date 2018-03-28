const debug = @import("std").debug;

const NumberType = enum {
    Increasing,
    Decreasing,
    IncreasingOrDecreasing,
    Bouncy,
};

const State = enum {
    IncreasingOrDecreasing,
    Increasing,
    Decreasing,
};

fn identify(n: u64) NumberType {
    var x = n;

    var maybe_last_digit: ?u64 = null;
    var state = State.IncreasingOrDecreasing;

    while (x != 0) : (x /= 10) {
        const digit = x % 10;

        if (maybe_last_digit) |last_digit| {
            switch (state) {
                State.IncreasingOrDecreasing => {
                    if (digit < last_digit) {
                        state = State.Increasing;
                    } else if (digit > last_digit) {
                        state = State.Decreasing;
                    }
                },
                State.Increasing => {
                    if (digit > last_digit) {
                        return NumberType.Bouncy;
                    }
                },
                State.Decreasing => {
                    if (digit < last_digit) {
                        return NumberType.Bouncy;
                    }
                },
            }
        }

        maybe_last_digit = digit;
    }

    return switch (state) {
        State.Increasing => NumberType.Increasing,
        State.Decreasing => NumberType.Decreasing,
        State.IncreasingOrDecreasing => NumberType.IncreasingOrDecreasing,
    };
}

fn run() u64 {
    var bouncy_seen: u64 = 19602;
    var i: u64 = 21780;

    while ((100 * bouncy_seen) / i != 99 or (100 * bouncy_seen) % i != 0) : (i += 1) {
        bouncy_seen += switch (identify(i)) {
             NumberType.Bouncy => u64(1),
             else => 0,
        };
    }

    return i;
}

pub fn main() void {
    debug.warn("{}\n", run());
}

test "112" {
    debug.assert(run() == 1587000);
}
