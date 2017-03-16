// - Walk from octagonal to triangular since the higher order values will
//   split the search space more rapidly.
//
// - The search space is fairly small, so a brute-force-ish approach seems
//   like the right way to go.
//
// - We can pre-generate all the numbers and place them in an array of 100
//   entries, ordered by the first two-digits that they occur in. This makes
//   traversal for the next values relatively quick.

/// Return a vector of 6 elements filled with 4-digit values satisfying the
/// required constraint. The first two-digits of these values are found in
/// the index of the cache, with the remaining two the lookup values.
fn cache_new() -> Vec<Vec<Vec<usize>>> {
    let mut v = vec![vec![vec![]; 100]; 3];

    // Compute all 4-digit numbers for each type, largest (octagonal) first
    //fill4(&mut v[0], |n| n*(3*n-2));    // octagonal
    //fill4(&mut v[1], |n| n*(5*n-3)/2);  // heptagonal
    //fill4(&mut v[2], |n| n*(2*n-1));    // hexagonal
    fill4(&mut v[0], |n| n*(3*n-1)/2);  // pentagonal
    fill4(&mut v[1], |n| n*n);          // square
    fill4(&mut v[2], |n| n*(n+1)/2);    // triangle

    v
}

/// Fills the input vector with elements of length 4-digits for the specified
/// function. The function is expected to monotonically increasing.
fn fill4<F: Fn(usize) -> usize>(v: &mut Vec<Vec<usize>>, f: F) {
    for value in (1..).map(|x| f(x)).skip_while(|&x| x < 1000).take_while(|&x| x < 10000) {
        v[value / 100].push(value % 100);
    }
}

/// Walk a filled cache-set and return the first result found
fn cache_walk(v: &Vec<Vec<Vec<usize>>>) -> Vec<usize> {
    let mut rs = Vec::with_capacity(v.len());


    // remember we can walk to any value next time, so must traverse through all
    // traverse forward and back at the same time

    for value in v[0] {
        if v[0].is_empty() {
            continue;
        }
    }

    rs
}

fn main() {
    // We effectively have a tree with which we need to walk through to the
    // first leaf node.
    let v = cache_new();
    //let rs = cache_walk(&v);
}
