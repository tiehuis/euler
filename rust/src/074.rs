/// Keep a list of chain lengths for every starting segment.
///
/// Compute chain lengths until we find a duplicate, and then cache the
/// length of every chain found.

use std::collections::HashSet;

static FACT: [usize; 10] = [
    1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880
];

/// Compute the digit factorial sum of n
fn digit_factorial(nn: usize) -> usize {
    let mut n = nn;
    let mut r = 0;
    while n != 0 {
        r += FACT[n % 10];
        n /= 10;
    }
    r
}

fn main() {
    // This does not store intermdiate values
    let mut lengths = vec![0; 1_000_000];

    let mut chain = Vec::new();
    let mut seen = HashSet::new();
    let mut count = 0;

    for i in 1..1_000_000 {
        // Reuse existing memory
        seen.clear();
        chain.clear();

        // initial chain value
        chain.push(i);

        // The found cached length of the chain
        let mut c = 0;

        loop {
            let last = digit_factorial(*chain.last().unwrap());

            // Check if we know how this chain ends
            if last < lengths.capacity() && lengths[last] != 0 {
                // Update cached length to have appropriate offset
                c = lengths[last];
                break;
            }

            // Seen this element in this chain, so we have encountered a dup
            if seen.contains(&last) {
                break;
            }

            chain.push(last);
            seen.insert(last);
        }

        if chain.len() + c == 60 {
            count += 1;
        }

        // Update cache for all chain values encountered during this sweep
        for (v, &i) in chain.iter().rev().enumerate() {
            if i < lengths.capacity() {
                lengths[i as usize] = c + v + 1;
            }
        }
    }

    println!("{:?}", count);
}
