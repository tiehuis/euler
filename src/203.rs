/// We do not want to factor the values themselves to determining if they
/// are square-free. Instead, we use the equation n!/k!(n-k)! and factorize
/// the components.

extern crate primal;

use std::collections::HashSet;

/// Combine a factor list with another. This is equivalent to multiplying
/// a number x by a number y, but working with their factors directly.
fn combine_factors(factors: &mut Vec<(usize, usize)>, ks: &Vec<(usize, usize)>) {
    // tuples are immutable, so we construct new tuples and remove old. This
    // can result in a potentially unsorted state.
    'outer: for &(f, c) in ks {
        for mut ft in factors.iter_mut() {
            if ft.0 == f {
                *ft = (f, c + ft.1);
                continue 'outer;
            }
        }

        // We did not find the factor, so add it as a new one
        match factors.iter().position(|&(ff, _)| ff > f) {
            Some(idx) => factors.insert(idx, (f, c)),
            None => factors.push((f, c))
        }
    }
}

/// Reduce factors from two lists of factors. This is equivalent to dividing a
/// number by another. If we cannot divide exactly, panic.
fn reduce_factors(factors: &mut Vec<(usize, usize)>, ks: &Vec<(usize, usize)>) {
    'outer: for &(f, c) in ks {
        for mut ft in factors.iter_mut() {
            if ft.0 == f {
                // panic on underflow if too many factors to reduce
                *ft = (ft.0, ft.1 - c);
                continue 'outer;
            }
        }

        // We did not find the factor, so panic
        panic!("could not find factor");
    }

    // Remove factors which are length 0
    factors.retain(|&(_, c)| c > 0);
}

/// Compute all prime factors of the specified factorial
fn factorial_factors(s: &primal::Sieve, n: usize) -> Vec<(usize, usize)> {
    assert!(s.upper_bound() >= n);

    // Factorize component-wise and combine
    let mut factors = Vec::new();
    for i in 1..(n+1) {
        let ks = s.factor(i).unwrap();
        combine_factors(&mut factors, &ks);
    }

    factors
}

/// Compute the binomial coefficient as a list of factors
fn binomial_factors(s: &primal::Sieve, n: usize, k: usize) -> Vec<(usize, usize)> {
    assert!(n >= k);

    // Compute n!/k!(n - k)!

    // n!
    let mut nf = factorial_factors(&s, n);

    // k!(n - k)!
    let mut kf = factorial_factors(&s, k);
    combine_factors(&mut kf, &factorial_factors(&s, n - k));

    // Reduce common factors
    reduce_factors(&mut nf, &kf);

    nf
}

/// Return true if the factors are squarefree
fn is_squarefree(factors: &Vec<(usize, usize)>) -> bool {
    factors.iter().all(|&(_, c)| c == 1)
}

fn main() {
    let sieve = primal::Sieve::new(100);
    let mut sum = 0_u64;

    // Keep track of seen squarefree values to avoid duplicates
    let mut seen = HashSet::new();

    for n in 1..51 {
        // Binomial function is symmetric across k
        for k in 1..(n+1)/2+1 {
            let factors = binomial_factors(&sieve, n, k);

            if is_squarefree(&factors) {
                let value = factors.iter().fold(1, |a, &(f, c)| a * (f * c) as u64);

                if !seen.contains(&value) {
                    seen.insert(value);
                    sum += value;
                }
            }
        }
    }

    println!("{}", sum);
}
