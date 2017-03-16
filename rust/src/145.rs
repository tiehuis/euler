/// Number must have different parities for the start and end values which
/// splits the search space in half.
///
/// Otherwise this is just a simple brute-force.

use std::collections::HashSet;

fn reverse(n: usize) -> usize {
}

fn main() {
    // We make use of a number of counting variables in order to skip obvious
    // non-reversible numbers.

    // Keep track of whether the leading term is even or odd.
    let mut leading_is_odd = false;

    // Keep track of how many digits the current values are
    let mut leading = 2;

    // Keep track of how many more iterations are required until we reach the
    // next number of digit counts.
    let mut remaining = 90;

    let mut i = 10;
    loop {
        if remaining < 0 {
            remaining = 10.powi(leading + 1) - 10.powi(leading);
            leading += 1;

            // 
            i += if leading_is_odd { 1 } else { -1 };
        }

        i += 1;
    }
}
