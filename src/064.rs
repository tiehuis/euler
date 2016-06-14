//! Use a standard algorithm to compute continued fractions and simply check
//! them all since the running time is linear with respect to the period.

use std::collections::HashMap;

//  Return true if `a` is a pefect square.
fn is_perfect_sq(a: i64) -> bool {
    let s = (a as f64).sqrt().trunc() as i64;
    s * s == a
}

// Compute the period length of a continued fraction of the form `sqrt(a)`
fn period_length(a: i64) -> usize {
    if a <= 0 || is_perfect_sq(a) {
        0
    } else {
        let mut a0 = (a as f64).sqrt().floor() as i64;
        let mut u0 = a0;
        let mut v0 = 1;

        // we have a period once we encounter the same parameters and where
        // they were seen.
        let mut seen = HashMap::<(i64, i64, i64), usize>::new();

        // count the length of the periodic part
        let mut count = 0_usize;

        loop {
            v0 = (a - u0 * u0) / v0;
            a0 = (((a as f64).sqrt() + u0 as f64) / (v0 as f64)).floor() as i64;
            u0 = a0 * v0 - u0;

            let k = (a0, u0, v0);
            if seen.contains_key(&k) {
                // slice the periodic part at the first element
                count = count - *seen.get(&k).unwrap();
                break;
            } else {
                seen.insert(k, count);
            }

            count += 1;
        }

        count
    }
}

fn main() {
    let mut count = 0;

    for i in 1..10_001 {
        let pl = period_length(i);
        if pl % 2 == 1 {
            count += 1;
        }
    }

    println!("{:?}", count);
}
