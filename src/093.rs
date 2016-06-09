/// We perform a slightly different approach. We construct an AST and shuffle
/// through all permutations of structure (brackets) and operations as well.

extern crate permutohedron;

use std::collections::HashSet;
use permutohedron::LexicalPermutation;

/// Return whether the specified integer has duplicate digits.
fn has_dup(nn: usize) -> bool {
    let mut n = nn;
    let mut seen = [false; 10];

    while n != 0 {
        let l = n % 10;
        if seen[l] {
            return true;
        }
        seen[l] = true;
        n /= 10;
    }

    false
}

/// Split an integer into a vector of its digits and return a vector
/// in sorted position.
fn split_integer(nn: usize) -> Vec<usize> {
    let v = Vec::with_capacity(10);

    while nn != 0 {
        v.insert(nn % 10);
        nn /= 10;
    }

    v.sort();
    v
}

/// Compute the longest sequence from 1..n
fn longest_seq4(set: &[usize]) -> usize {
    assert!(set.len() == 4);

    // Construct an ast for each ordering of the set
}

fn main() {
    let mut seen = HashSet::new();

    let r = (1234..9877).map(|x| {
                if has_dup(i) || seen.contains(&i) {
                    0
                } else {
                    seen.insert(&i);
                    longest_seq4(&split_integer(i))
                }
            }).max()

    println!("{:?}", r);
}
