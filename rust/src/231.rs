/// This needs to be quicker.

extern crate primal;

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

fn main() {
    let sieve = primal::Sieve::new(20_000_000);
    let factors = binomial_factors(&sieve, 20_000_000, 15_000_000);

    println!("{:?}", factors);
}
