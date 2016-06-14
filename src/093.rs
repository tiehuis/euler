/// We construct expressions as a string, then evaluate it to obtain the
/// result.
///
/// This is an extremely convoluted way of doing things.

#[macro_use]
extern crate pest;
extern crate permutohedron;

use std::collections::BinaryHeap;

use permutohedron::LexicalPermutation;
use pest::prelude::*;

impl_rdp! {
    grammar! {
        expr = _{
            { ["("] ~ expr ~ [")"] | num }
            add  = { plus | minus }
            mult = { times | slash }
        }
        num   = @{ ['1'..'9'] }
        plus  = { ["+"] }
        minus = { ["-"] }
        times = { ["*"] }
        slash = { ["/"] }
        whitespace = _{ [" "] }
    }

    process! {
        (&self) -> i32 {
            (&num: num) => {
                num.parse::<i32>().unwrap()
            },
            (_: add, @left, sign, @right) => {
                match sign.rule {
                    Rule::plus => left + right,
                    Rule::minus => left - right,
                    _ => unreachable!()
                }
            },
            (_: mult, @left, sign, @right) => {
                match sign.rule {
                    Rule::times => left * right,
                    Rule::slash => if right != 0 {
                        left / right
                    } else {
                        // This is a hack, but with the input numbers and us
                        // filtering out negatives it works fine. Better than
                        // catching panics.
                        -1_000_000
                    },
                    _ => unreachable!()
                }
            }
        }
    }
}

/// Fill a number of similar format strings at once. This is required as a
/// macro since we cannot do dynamic format string generation.
///
/// We specify parameters one-by-one since we cannot perform in lockstep
macro_rules! template {
    ($($fmt:expr),* ; $p1:expr, $p2:expr, $p3:expr, $p4:expr, $p5:expr, $p6:expr, $p7:expr) => {
        {
            let mut filled = Vec::new();
            $(
                filled.push(format!($fmt, $p1, $p2, $p3, $p4, $p5, $p6, $p7));
            )*
            filled
        }
    };
}

/// Compute the longest sequence for the specified values
fn compute_sequence(v: &mut [usize]) -> usize {
    assert_eq!(v.len(), 4);

    let mut heap = BinaryHeap::new();

    // Iterate over all possible orderings of v
    loop {
        // Iterate over all possible operator choices
        for oo in 0..64 {
            let op_map = [ "+", "-", "*", "/" ];

            let o = [
                op_map[oo & 3], op_map[(oo >> 2) & 3], op_map[(oo >> 4) & 3]
            ];

            let ss = template!(
                // vl  op  vl  op  vl  op  vl
                "  {}  {}  {}  {}  {}  {}  {}  ",
                " ({}  {}  {}) {}  {}  {}  {}  ",
                " ({}  {}  {}  {}  {}) {}  {}  ",
                "  {}  {} ({}  {}  {}) {}  {}  ",
                "  {}  {} ({}  {}  {}  {}  {}) ",
                "  {}  {}  {}  {} ({}  {}  {}) ",
                " ({}  {}  {}) {} ({}  {}  {}) ",
                " ({}  {} ({}  {}  {})){}  {}  ",
                "(({}  {}  {}) {}  {}) {}  {}  ",
                "  {}  {}(({}  {}  {}) {}  {}) ",
                "  {}  {} ({}  {} ({}  {}  {}))"
                ;
                v[0], o[0], v[1], o[1], v[2], o[2], v[3]
            );

            for s in ss {
                let mut parser = Rdp::new(StringInput::new(&s));
                assert!(parser.expr());
                heap.push(parser.process())
            }
        }

        if !v.next_permutation() {
            break;
        }
    }

    let mut sh = heap.into_sorted_vec();
    sh.dedup();
    sh.retain(|&x| x > 0);

    if !sh.is_empty() && sh[0] == 1 {
        for i in 0..sh.len()-1 {
            if sh[i] + 1 != sh[i + 1] {
                return i + 1
            }
        }
        sh.len()
    } else {
        0
    }
}

fn main() {
    let mut max = 0;
    let mut can = 0;

    for d in 4..9 {
        for c in 3..d {
            for b in 2..c {
                for a in 1..b {
                    let values = compute_sequence(&mut [a, b, c, d]);
                    if values > max {
                        max = values;
                        can = a * 1000 + b * 100 + c * 10 + d;
                    }
                }
            }
        }
    }

    println!("{} {}", max, can);
}
