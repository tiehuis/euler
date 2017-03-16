/// This is simply an exercise in implementing the partition function.
///
/// Further, we also have the fact that p(5k + 4) == 0 (mod 5), so for
/// divisibility by 1 million, we can narrow the search space a bit.
///
/// This is not an iff however, so this may not hold.

use std::cmp;

type PartitionCache = Vec<usize>;

const CACHE_LIMIT: usize = 1_000_000;

/// Return a cache for use when calculating partitions.
fn partition_cache(n: usize) -> PartitionCache {
    let mut values = vec![0; cmp::min(n, CACHE_LIMIT)];

    // Fill with default initial values as a base case
    values[0] = 0;
    values[1] = 1;
    values[2] = 2;
    values[3] = 3;
    values[4] = 5;
    values[5] = 7;

    values
}

/// Compute the partition function of a specified number using the
/// given cache of values.
fn partition_memoize(mut pc: &mut PartitionCache, n: usize) -> usize {
    // If the value is cached, return immediately
    if n < pc.capacity() && pc[n] != 0 {
        pc[n]
    } else {
        let mut sum = 0_i64;
        for k in 1..n {
            let sign = if k % 2 == 1 { 1 } else { -1 };

            println!("{} {}", n, k);
            let x = partition_memoize(&mut pc, n - k*(3*k - 1)/2);
            let y = partition_memoize(&mut pc, n - k*(3*k + 1)/2);

            println!("{}: {} {}", n, x, y);
            sum += sign * (x + y) as i64;
        }

        assert!(sum >= 0);

        // Add value to cache
        if n < pc.capacity() {
            pc[n] = sum as usize;
        }

        sum as usize
    }
}

fn main() {
    let mut cache = partition_cache(1_000);
    for i in 1..100 {
        println!("{}", partition_memoize(&mut cache, i));
    }
}
