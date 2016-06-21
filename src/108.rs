/// We are given the following 1/x + 1/y = 1/n
///
/// We can simplify this into a diophantine equation
///     n(y + x) = xy
///     => xy + ny + nx = 0
///
/// With solutions
///     n + x != 0, y = -nx/(n + x)
///
/// Now given a known n, we get the following expression
///     y = -nx/(n + x)
///     => (n + x)y = -nx
///     => ny + xy + nx = 0
///
/// This can be solved with a generic solver for the simple hyperbolic
/// case of quadratic diophantine equations.
///
/// The number of solutions for a given n is equivalent to the number of
/// divisors of n^2.

extern crate primal;

fn main() {
    let sieve = primal::Sieve::new(1_000_000);

    // The number of solutions of the equation `xy + ny + nx = 0` is related
    // directly to the number of divisors of n^2.
    //
    // We have two solutions per divisor found
    let k = (1..).find(|&x| {
                // We need to look for 2 * 1000 since we are counting
                // solutions on divisors twice.
                sieve.factor(x).unwrap().iter()
                     .fold(1, |a, &(_, c)| a * (2 * c + 1)) > 2000
            });

    println!("{:?}", k.unwrap());
}
