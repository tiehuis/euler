/// Simple divisor function implementation for sigma_2(x).
///
/// # Bruteforce
/// We can improve the performance by working backwards, constructing
/// all integer values by iterating through prime decompositions.
///
/// # Square Relation
/// We can reduce the number of primes we need to iterate through by
/// noting that the divisor sum must be a square.
///
/// sigma_2(n) = product_{i=1}^{r}(1 + p_i^x + p_i^{2} + ... + p_i^{a_i*2})
///
/// If sigma_2(n) is square, then (1 + p_i ...) must be a square as well.
/// This is only square when the sum of prime powers of 2 are 1 less than a
/// square.
///
/// # Example
/// 10 = 2 * 5
///
/// sigma_2(10 = 2*5) = (1 + 2^2) * (1 + 5^2)
///                   = 5 * 26
///                   = 130
///
/// 1 + a^2 + a^4 + a^6 = 1 + a^2(1 + a^2(1 + a^2)) must be perfect square
///
/// If a is odd, then the factor must be even and vice-versa and so:

fn main() {

}
