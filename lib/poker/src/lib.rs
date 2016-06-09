/// Evaluate poker hands.

static LOOKUP_TABLE: [i32; 40] = [
    0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0, 0,
    0, 0, 0, 0, 0, 0x1000, 0, 0x4000, 0x2000, 0,
    0, 0, 0x8000, 0, 0x200, 0x800, 0, 0, 0, 0,
    0, 0x400, 0, 0x10000, 0x100, 0, 0, 0, 0, 0
];

pub fn eval5(a: &str, b: &str, c: &str, d: &str, e: &str) -> Option<i32> {
    macro_rules! conv {
        ($x:expr) => {{
            let mut bytes = $x.bytes();
            let a = bytes.next();
            let b = bytes.next();

            if a.is_none() || b.is_none() {
                return None;
            }

            LOOKUP_TABLE[a.unwrap() as usize - 50] | LOOKUP_TABLE[b.unwrap() as usize - 50]
        }}
    };

    let aa = conv!(a);
    let bb = conv!(b);
    let cc = conv!(c);
    let dd = conv!(d);
    let ee = conv!(e);

    Some(eval5_internal(aa, bb, cc, dd, ee))
}

fn eval5_internal(a: i32, b: i32, c: i32, d: i32, e: i32) -> i32 {
    let x = (a ^ b ^ c ^ d ^ e) & 0x1fff;
    let y = (a | b | c | d | e) & 0x1fff;
    let z = y ^ x;

    let mut v = y & (y - 1);
    v &= v - 1;
    let v = if v == 0 {
        2
    } else {
        v &= v - 1;
        if v == 0 {
            3
        } else {
            v &= v - 1;
            if v == 0 {
                4
            } else {
                5
            }
        }
    };

    match v {
        4 => 0x4000000 | x | (z << 13),
        3 => {
            if z != 0 {
                0x800000 | x | (z << 13)
            } else {
                0xc000000
                | if (a & b) == (a & 0x1fff) {
                    a
                } else if (c & d) == (c & 0x1fff) {
                    c
                } else {
                    e
                }
                & 0x1fff ^ y | (v << 13)
            }
        }
        2 => {
            if (a + b + c + d + e - x) & 0x1fff == 0x1fff & ((y ^ x) << 2) {
                0x1c000000 | x | (z << 13)
            } else {
                0x18000000 | z | (x << 13)
            }
        }
        _ => {
            let s = 0x1f1d100 % y == 0;
            let f = (a & b & c & d & e) != 0;
            if s && f {
                0x20000000 | if x == 0x100f { 15 } else { x }
            } else if s {
                0x10000000 | if x == 0x100f { 15 } else { x }
            } else if f {
                0x1f000000 | x
            } else {
                x
            }
        }
    }
}
