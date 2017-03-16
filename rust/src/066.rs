/// This is simply an evaluation of a quadratic diophantine equation.
///
/// The equation in question is always of the hyperbolic case (discriminant
/// b^2 - 4ac > 0) and so this is a problem in implementing one general
/// solver.

/// Generic solver for equations of the form Ax^2 + Cy^2 + F = 0 where
/// F != 0 and b^2 - 4ac is not a perfect square.
///
/// This matches the requirements for the equation x^2 - Dy^2 - 1 = 0.
fn solve(a: i32, c: i32, f: i32) -> (x, y) {
    // Require: f | gcd(a, c) which is always true since f is -1

    // a == 1 and f == -1 and so 4*f*f < -4*a*c evaluates to 4 < -4*c.
    // We evaluate c as a negative always and for values > 1 and so
    // 4*f*f < -4*a*c for all cases.

    // The value of b is zero, so we do not need to perform a simplification
    // to reduce it.
    //
    // We can assume gcd(x, y) == 1.
    //
    // Let x = sy - fz and so
    //
    // (sy-fz)^2 + cy^2 - 1 = 0
    //
    // (sy)^2 - 2fz + (fz)^2 + cy^2 = 1
    //
    // Must now determine values 0 <= s < f - 1 st. as^2 + c == 0 (mod f).
    //
    // Calculate the continued fraction expansion of (cs^2 + a)t^2 + 2cst + c = 0.
}

fn main() {
}
