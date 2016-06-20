/// There are only 10 possible digits to use. If we were to iterate over all
/// possible permutations, this is only 10! ~= 3.6m possibilities. This is
/// small enough that brute-forcing seems like a valid option even without
/// any obvious filtering.

extern crate permutohedron;

use permutohedron::LexicalPermutation;

fn main() {
    let mut seq = vec![1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
    let mut max = "".to_string();

    loop {
        // The first permutation does not work, and we always want to
        // perform a permutation on each pass.
        if !seq.next_permutation() {
            break;
        }

        // Since this is a 16-digit string, 10 cannot occur in a shared slot
        if seq[2] == 10 || seq[4] == 10 || seq[6] == 10 || seq[8] == 10 {
            continue;
        }

        // We are only interested in orderings where the smallest corner value
        // is in the first slot
        if seq[3] < seq[0] || seq[5] < seq[0] || seq[7] < seq[0] || seq[9] < seq[0] {
           continue;
        }

        // first line
        let sum = seq[0] + seq[1] + seq[2];

        // second line
        if seq[3] + seq[2] + seq[4] != sum {
            continue;
        }

        // third line
        if seq[5] + seq[4] + seq[6] != sum {
            continue;
        }

        // fourth line
        if seq[7] + seq[6] + seq[8] != sum {
            continue;
        }

        // fifth line
        if seq[9] + seq[8] + seq[1] != sum {
            continue;
        }

        // Construct a bit string from the result vector
        let s = seq.iter().map(|x| x.to_string()).collect::<Vec<_>>();

        // We need to reserve new space hence the clone, and we only require
        // references from the indexed content.
        let bs = s[0].clone() + &s[1] + &s[2] + &s[3] + &s[2] + &s[4] + &s[5] +
                &s[4] + &s[6] + &s[7] + &s[6] + &s[8] + &s[9] + &s[8] + &s[1];

        if bs.len() == 16 && bs > max {
            max = bs;
        }
    }

    println!("{}", max);
}
