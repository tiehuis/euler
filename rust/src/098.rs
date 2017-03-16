/// Read words into a vector of values which are anagrams of each other.
/// Compute the squares of each set of anagrams and find the highest.

use std::collections::HashMap;
use std::io;
use std::io::prelude::*;
use std::fs::File;
use std::iter::FromIterator;

/// Read a file into a hashmap from the integer value of the ordered
/// string to a list of found strings.
fn read_file(filename: &str) -> HashMap<String, Vec<String>> {
    let mut f = File::open(filename).unwrap();
    let mut buffer = String::new();
    f.read_to_string(&mut buffer).unwrap();

    let mut hm = HashMap::<String, Vec<String>>::new();
    for word in buffer.split(',') {
        let w = word.trim_matches('"');
        let mut v: Vec<char> = w.chars().collect();
        v.sort();
        let ws = String::from_iter(v);

        let entry = hm.entry(ws).or_insert(vec![]);
        entry.push(w.to_string());
    }

    hm
}

fn main() {
    let v = read_file("res/p098_words.txt");

    for (k, v) in v.iter() {
        if v.len() <= 1 {
            continue;
        }

        // Just bruteforce substitutions

        // Make a substitution for each letter checking if it is square
        let vs = (v as f32).sqrt();
        if vs == vs.trunc() {
        }
    }
}
