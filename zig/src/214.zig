const std = @import("std");
const debug = std.debug;
const mem = std.mem;
const Allocator = mem.Allocator;

fn totient_sieve(allocator: &Allocator, limit: usize) ![]usize {
    var phis = try allocator.alloc(usize, limit + 1);

    for (phis) |*phi, i| {
        *phi = i;
    }

    for (phis[2..]) |phi, ii| {
        const i = 2 + ii;
        if (phi == i) {
            var j = i;
            while (j < phis.len) : (j += i) {
                phis[j] -= @divExact(phis[j], i);
            }
        }
    }

    return phis;
}

fn run(comptime L: usize, comptime n: usize) !u64 {
    const phis = try totient_sieve(std.heap.c_allocator, n);
    defer std.heap.c_allocator.free(phis);

    var sum: u64 = 0;
    for (phis) |cphi, i| {
        // phi(n) = n - 1 where n is prime
        if (i != cphi + 1) {
            continue;
        }

        var phi = cphi;
        var chain_len: usize = 2;
        while (phi > 1) : (chain_len += 1) {
            phi = phis[phi];
        }

        if (chain_len == L) {
            sum += i;
        }
    }

    return sum;
}

pub fn main() !void {
    debug.warn("{}\n", try run(25, 40000000));
}

test "214" {
    debug.assert((try run(25, 40000000)) == 1677366278943);
}
