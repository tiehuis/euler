/// The resilience is directly related to phi(n).
///
/// We are looking to minimize phi(n) / (n - 1). The value we are searching
/// for will be sandwiched between primorials. We can search for the smallest
/// primorial which satisfies the given constraint, then work backwards, adding
/// small prime powers until we reach the point where the value no longer
/// satisfies the constraint.

extern crate primal;

/// Compute the totient function given a vector of prime factors.
fn phi(factors: &Vec<(usize, usize)>) -> usize {
    factors.iter().fold(1, |a, &(f, c)| a * f.pow(c as u32 - 1) * (f - 1))
}

fn main() {
    /*
    const LIMIT: usize = 1_000_000;

    let ps = primal::Sieve::new(LIMIT);
    let x = (1..LIMIT).find(|&x| {
        let fs = ps.factor(x).unwrap();
        let ratio = phi(&fs) as f64 / (x - 1) as f64;
        ratio < (18000_f64 / 94744_f64)
    });

    println!("{:?}", x);
    */

    let ps = primal::Sieve::new(500);

    let mut primorial = 1;
    for p in ps.primes_from(0) {
        primorial *= p;
        let fs = ps.factor(primorial).unwrap();
        let ratio = phi(&fs) as f64 / (primorial - 1) as f64;
        if ratio < (15499_f64 / 94744_f64) {
            break;
        }
    }

    println!("{}", primorial);
}
