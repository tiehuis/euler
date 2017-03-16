//! Standard brute-force approach over all orderings.

#[macro_use]
extern crate itertools;
extern crate permutohedron;

use permutohedron::LexicalPermutation;

// Compute all different permutations of arithmetic expressions and calculate
// the longest consecutive sequence from 1.
fn succ_number(iv: &mut [i32]) -> usize {
    // Assume sequence is less than 1000
    let mut check = [false; 1000];

    loop {
        // We need to work with floats else we get integer rounding!
        let v: Vec<f32> = iv.iter().map(|&x| x as f32).collect();

        for (op1, op2, op3) in iproduct!(0..4, 0..4, 0..4) {
            // Evaluate a float expression, breaking on division by zero.
            macro_rules! o {
                ($left:expr, $op:expr, $right:expr) => {
                    match $op {
                        0 => $left + $right,
                        1 => $left - $right,
                        2 => $left * $right,
                        3 => {
                            if $right == 0_f32 { break; }
                            $left / $right
                        },
                        x @ _ => panic!("invalid operand encountered: {}", x)
                    }
                }
            }

            // Try add the evaluation to the check array if it is small enough
            // and is an integer.
            macro_rules! add {
                ($c:expr, $x:expr) => {
                    loop {
                        let r = $x;
                        if 0_f32 < r && r <= $c.len() as f32 && r.floor() == r {
                            $c[r as usize] = true;
                        }
                        break;
                    }
                }
            }

            // 1 * 2 * 3 * 4
            add!(check, o!(v[3], op3, o!(v[2], op2, o!(v[1], op1, v[0]))));

            // 1 * (2 * 3) * 4
            add!(check, o!(v[3], op3, o!(o!(v[2], op2, v[1]), op1, v[0])));

            // 1 * 2 * (3 * 4)
            add!(check, o!(o!(v[3], op3, v[2]), op2, o!(v[1], op1, v[0])));

            // 1 * (2 * 3 * 4)
            add!(check, o!(o!(v[3], op3, o!(v[2], op2, v[1])), op1, v[0]));

            // (1 * 2) * (3 * 4)
            add!(check, o!(o!(v[3], op3, v[2]), op2, o!(v[1], op1, v[0])));
        }

        if !iv.next_permutation() {
            break;
        }
    }

    check.into_iter().skip(1).take_while(|&&x| x == true).count()
}

fn main() {
    let r = iproduct!(1..10, 1..10, 1..10, 1..10)
                .filter(|&(a, b, c, d)| a < b && b < c && c < d)
                .map(|(a, b, c, d)| (1000 * a + 100 * b + 10 * c + d,
                                     succ_number(&mut [a, b, c, d]))
                )
                .max_by_key(|x| x.1)
                .unwrap();

    println!("{}", r.0);
}
