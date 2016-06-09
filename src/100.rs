/// We are giving the following constraints
///
///     (b/t)*((b-1)/(t-1)) = 1/2
/// and
///     b + r >= t where t <= 1e12
///
/// Simplifying
///     2b^2 - 2b - t^2 + t = 0
///
/// Matches the diophantine equation:
///     Ax^2 + Bxy + Cy^2 + Dx + Ey + F = 0
///
/// With coefficients
///     A: 2
///     B: 0
///     C: -1
///     D: -2
///     E: 1
///     F: 0
///
/// We get the following congruences:
///     P: 3
///     Q: 2
///     K: -2
///     R: 4
///     S: 3
///     L: -3
///
/// Which map to the given sequences of solutions:
///     Xn+1 = 3*Xn + 2*Yn - 2
///     Yn+1 = 4*Xn + 3*Yn - 3
///
/// Iterate until Y (the total number of discs) exceeds 1e12

fn main() {
    let mut xn = 15_u64;
    let mut yn = 21_u64;

    while yn < 1e12 as u64 {
        let tn = xn;
        xn = 3*xn + 2*yn - 2;
        yn = 4*tn + 3*yn - 3;
    }

    println!("{}", xn);
}
