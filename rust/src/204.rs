/// This is just a problem of iterating through all combinations of prime
/// factors less than 100 and building the numbers in an efficient way.

extern crate primal;

fn main() {
    let sieve = primal::Sieve::new(100);
    let v = vec![0; 25]; // There are 25 primes < 100
}
