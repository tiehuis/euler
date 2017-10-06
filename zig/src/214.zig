const std = @import("std");
const Allocator = std.mem.Allocator;

fn totient_sieve(allocator: &Allocator, limit: usize) -> %[]usize {
    var phis = %return allocator.alloc(usize, limit + 1);

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

    phis
}

fn run(comptime L: usize, comptime n: usize) -> %u64 {
    var allocator = @import("../lib/c_allocator.zig").c_allocator;

    const phis = %return totient_sieve(&allocator, n);
    defer allocator.free(phis);

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

    sum
}

pub fn main() -> %void {
    %%std.io.stdout.printf("{}\n", %%run(25, 40000000));
}

test "214" {
    std.debug.assert(%%run(25, 40000000) == 1677366278943);
}
