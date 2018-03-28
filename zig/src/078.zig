const std = @import("std");
const debug = std.debug;
const mem = std.mem;
const Allocator = mem.Allocator;
const ArrayList = std.ArrayList;

fn Partition(comptime mod: u8) type {
    return struct {
        const Self = this;
        const digit_count = comptime blk: {
            var r: i64 = 1;
            var i: u8 = 1;
            while (i < mod) : (i += 1) {
                r *= 10;
            }
            break :blk r;
        };

        allocator: &Allocator,
        partitions: ArrayList(i64),
        n: usize,

        pub fn init(allocator: &Allocator) Self {
            return Self {
                .allocator = allocator,
                .partitions = ArrayList(i64).init(allocator),
                .n = 0,
            };
        }

        pub fn deinit(p: &Self) void {
            p.partitions.deinit();
        }

        fn sign_m1(x: i64) i64 {
            return if (@mod(x, 2) == 0) i64(1) else -1;
        }

        pub fn next(p: &Self) !i64 {
            if (p.partitions.len == 0) {
                try p.partitions.appendSlice([]i64 { 1, 1, 2 });
            }

            const parts = p.partitions.toSliceConst();

            if (p.n < 3) {
                const result = parts[p.n];
                p.n += 1;
                return result;
            }

            var v: i64 = 0;
            var k: i64 = 1;
            var n = i64(parts.len);

            while (n >= @divFloor(k * (3 * k - 1), 2)) {
                v += sign_m1(k - 1) * parts[usize(n - @divFloor(k * (3 * k - 1), 2))];
                k += 1;
            }

            k = -1;
            while (n >= @divFloor(k * (3 * k - 1), 2)) {
                v += sign_m1(k - 1) * parts[usize(n - @divFloor(k * (3 * k - 1), 2))];
                k -= 1;
            }

            const final = @mod(v, digit_count);
            try p.partitions.append(final);
            return final;
        }
    };
}

fn run() u64 {
    var p = Partition(7).init(std.heap.c_allocator);
    defer p.deinit();

    var n: u64 = 0;
    while (true) : (n += 1) {
        if ((p.next() catch unreachable) == 0) {
            return n;
        }
    }
}

pub fn main() !void {
    try debug.warn("{}\n", run());
}

test "078" {
    debug.assert(run() == 55374);
}
