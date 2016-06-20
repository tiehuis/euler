// Should work backwards from known primes
//
// Cannot alter the final digit.
//
// Each prime must have similar digits, look for primes with repeated digits
// and sort based on the position where these repeated digits occur.
//
// We expect that it is probably a three-way substitution at least.

extern crate primal;

use std::collections::HashMap;
use std::usize;

// 10 is out of range of [0-9]
const ANY: usize = 10;

fn digit_repetitions(n: usize) -> Vec<Vec<usize>> {
    // Keep track of the position in the integer where the value
    // was found.
    let mut reps = vec![vec![]; 10];

    // We cannot use the final digit
    let mut m = n / 10;
    let mut position = 1;
    let mut digits = vec![n % 10];

    while m != 0 {
        let last = m % 10;
        digits.push(last);
        reps[last].push(position);
        position += 1;
        m /= 10;
    }

    // Store the available subsets this prime can belong to.
    let mut sets = Vec::new();

    // We need to iterate over every possible subset of a rep. We can do
    // this through a binary counting method. We can guarantee < 10
    // elements in each set so this is O(2^9) worst case.
    for rep in reps {
        if rep.len() < 3 {
            continue;
        }

        // Discard the empty subset
        for subset in 1..2_usize.pow(rep.len() as u32) {
            // Copy the digits and set the specified to any for all subsets in
            // the changeable region.
            let mut ss = digits.clone();
            for i in 0..rep.len() {
                if subset & (1 << i) != 0 {
                    ss[rep[i]] = ANY;
                }
            }

            ss.reverse();
            sets.push(ss);
        }
    }

    sets
}

fn ilog10(mut n: usize) -> usize {
    let mut c = 0;
    while n != 0 {
        n /= 10;
        c += 1;
    }
    c
}

fn main() {
    const TARGET: usize = 8;

    let mut rep = HashMap::<Vec<usize>, usize>::new();

    // We need to scan by powers of 10 to ensure we get the smallest. They
    // may not appear in order;
    let sieve = primal::Sieve::new(1_000_000);

    // Matches which have the right length
    let mut matches = Vec::new();

    // Keep track of whether we are the next power of 10
    let mut curr_log10_len = 1;

    'outer: for p in sieve.primes_from(2) {
        // Only scan for primes with repeated digits of length 2 or more
        // (excluding the final digit)
        let scans = digit_repetitions(p);

        for scan in scans {
            if let Some(value) = rep.get(&scan) {
                if value + 1 >= TARGET {
                    matches.push(scan.clone());
                }
            }

            let count = rep.entry(scan).or_insert(0);
            *count += 1;
        }

        let log10_len = ilog10(p);

        // We can break early if we have seen a match and have a power of 10.
        if matches.len() > 0 && curr_log10_len != log10_len {
            break;
        }

        curr_log10_len = log10_len;
    }

    let mut min = usize::MAX;
    for mh in matches {
        for g in 0..10 {
            let mut result = 0;
            let mut l10 = 1;
            for &i in mh.iter().rev() {
                result = result + if i == ANY { g } else { i } * l10;
                l10 *= 10;
            }

            if sieve.is_prime(result) {
                if result < min {
                    min = result;
                }
            }
        }
    }

    println!("{}", min);
}
