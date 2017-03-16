/// Quickest to just calculate sequences of squares less than the specified
/// limit and determine if they are palindromic.
///
/// The highest value needed to be calculated is 10^4, since 10^4*10^2 = 10^8.

use std::collections::HashSet;

fn is_palindrome(n: u64) -> bool {
    let mut nn = n;
    if n % 10 == 0 {
        false
    } else {
        let mut r = 0;
        while r < nn {
            r = 10 * r + nn % 10;
            nn /= 10;
        }
        nn == r || nn == r / 10
    }
}

// Minor problem with something here
fn main() {
    let mut seen = HashSet::new();
    let mut total_sum = 0_u64;

    // Compute sequences from the specified start point
    'outer: for n in 1..100_000 {
        let mut sum = n * n;
        for i in (n+1).. {
            // sequence must be at least length two
            sum += i * i;

            if sum >= 100_000_000 {
                continue 'outer;
            }

            if is_palindrome(sum) && !seen.contains(&sum) {
                total_sum += sum;
                seen.insert(sum);
            }
        }
    }

    println!("{}", total_sum);
}
