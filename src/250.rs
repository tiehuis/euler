// Precompute an array of congruences mod 250. This is quick with the
// module exponentiation algorithm. Next apply a standard subset
// sum matching algorithm, keeping track of the indices which match.
//
// Finally, compute the actual sums mod 10^16 to get the final value.

/// Binary modular exponentiation.
fn modexp(base: usize, exponent: usize, modulus: usize) -> usize {
    if modulus == 1 {
        0
    } else {
        let mut r = 1;
        let mut b = base % modulus;
        let mut e = exponent;

        while e > 0 {
            if e & 1 == 1 {
                r = (r * b) % modulus;
            }
            e >>= 1;
            b = (b * b) % modulus;
        }

        r
    }
}

/// Compute the congruences of the subset.
fn precompute_congruences(limit: usize) -> Box<[u8]> {
    (1..limit).map(|x| modexp(x, x, 250) as u8)
            .collect::<Vec<_>>()
            .into_boxed_slice()
}

fn main() {
    let congruences = precompute_congruences(250);

    // Use dynamic programming to determine which subsets sum to 0

    println!("{:?}", congruences);
}
