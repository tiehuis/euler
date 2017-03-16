/// Look at the following bn:
///
/// http://mathworld.wolfram.com/EulerTransform.html

extern crate primal;

use std::collections::HashMap;

/// Represents cached data that is used between successive calls to the
/// prime partition counting function.
///
/// The implementation of the prime counting function is based on Euler's
/// Transform.
struct PrimePartition {
    /// A sieve of prime to use when factoring
    sieve: primal::Sieve,

    /// Cached distinct prime factor products
    factor_cache: HashMap<usize, usize>,

    /// Cached count function sums
    count_cache: HashMap<usize, usize>,
}

impl PrimePartition {
    /// Generate a new partition counting implementation with support for
    /// up to the value `n`.
    pub fn new(n: usize) -> PrimePartition {
        PrimePartition {
            sieve: primal::Sieve::new(n),
            factor_cache: HashMap::new(),
            count_cache: HashMap::new()
        }
    }

    /// Count the number of prime partitions of `n`.
    ///
    /// # Asserts
    /// `n` <= PrimePartition::n
    pub fn count(&mut self, n: usize) -> usize {
        if n == 0 {
            1
        } else if self.count_cache.contains_key(&n) {
            *self.count_cache.get(&n).unwrap()
        } else {
            let result = (self.fprod(n) + (1..n).fold(0, |sum, k| {
                sum + self.fprod(k) * self.count(n - k)
            })) / n;
            self.count_cache.insert(n, result);
            result
        }
    }

    /// Return the product of distinct prime factors of `n`.
    fn fprod(&mut self, n: usize) -> usize {
        *self.factor_cache.entry(n).or_insert(
            self.sieve.factor(n).unwrap().into_iter()
                      .fold(0, |sum, (p, _)| sum + p)
        )
    }
}

fn main() {
    // We calculate the euler transform to compute prime partitions
    // The main equation is:
    // `b_n = 1/n[c_n + Sigma_{k=1}^{n-1}c_k b_{n-k}`
    //     where `c_n = Sigma_{d|n}d*a_d`
    //         where `a_n = 1 if n is prime, 0 if n is composite`
    let mut state = PrimePartition::new(1000);

    println!("{}", (0..1000).find(|&x| state.count(x) > 5000).unwrap());
}
