extern crate permutohedron;

use permutohedron::LexicalPermutation;

/// Represents a sub-graph of partitioned 4-element fields.
type Group = Vec<Vec<usize>>;

/// `f` is expected to be a monotonically increasing function.
fn make_group<F>(func: F) -> Group
    where F: Fn(usize) -> usize
{
    let mut map = vec![vec![]; 100];
    let result = (1..).map(func)
                     .skip_while(|&x| x < 1000)
                     .take_while(|&x| x < 10000);

    for value in result {
        let (hd, tl) = (value / 100, value % 100);
        map[hd].push(tl)
    }

    map
}

pub struct Walker<'a> {
    /// The order in which we will traverse the groups.
    indices: &'a [usize],

    /// The set of groups for each function.
    groups: &'a [Group],

    /// The initial prefix of the chain
    start: usize
}

impl<'a> Walker<'a> {
    /// Construct a new walker over a set of groups.
    pub fn new(indices: &'a [usize], groups: &'a [Group]) -> Walker<'a> {
        Walker { start: 0, indices, groups }
    }

    /// Walk the set of groups for a single-chain.
    ///
    /// Returns the chain if one was found.
    pub fn walk(&mut self) -> Option<Vec<(usize, usize)>> {
        let length = self.groups[self.indices[0]].len();

        for i in 0..length {
            for ref suffix in &self.groups[self.indices[0]][i] {
                self.start = i;
                match self.walk_chain(**suffix, 1) {
                    Some(mut v) => {
                        v.push((self.start, **suffix));
                        return Some(v)
                    }

                    None => ()
                }
            }
        }

        None
    }

    /// Walk a single direction for the specified prefix.
    fn walk_chain(&self, prefix: usize, depth: usize)
        -> Option<Vec<(usize, usize)>>
    {
        // wraparound and check the complete chain
        if depth >= self.indices.len() {
            if prefix == self.start {
                Some(vec![])
            } else {
                None
            }
        } else {
            for ref suffix in &self.groups[self.indices[depth]][prefix] {
                match self.walk_chain(**suffix, depth + 1) {
                    Some(mut v) => {
                        v.push((prefix, **suffix));
                        return Some(v);
                    }

                    None => ()
                }
            }

            None
        }
    }
}

fn result() -> Vec<(usize, usize)> {
    let groups = [
        make_group(|n| n*(n+1)/2),
        make_group(|n| n*n),
        make_group(|n| n*(3*n-1)/2),
        make_group(|n| n*(2*n-1)),
        make_group(|n| n*(5*n-3)/2),
        make_group(|n| n*(3*n-2))
    ];

    let mut indices: Vec<_> = (0..groups.len()).collect();
    loop {
        {
            let mut walker = Walker::new(&indices, &groups);
            match walker.walk() {
                Some(v) => {
                    return v;
                }

                _ => ()
            }
        }

        if !indices.next_permutation() {
            break;
        }
    }

    unreachable!()
}

fn main() {
    let r = result();
    println!("{}", r.iter().fold(0, |acc, &(hd, tl)| acc + (100 * hd + tl)));
}
