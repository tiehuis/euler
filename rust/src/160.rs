/// The trailing digits of a factorial are determined by the factors of
/// 2 and 5 present in the number.
///
/// We compute the factorial mod 100_000, and for each input number we first
/// filter out factors of 5 and 2 and keep a differential between the two.
///
/// Once we have computed the final value, we add this differential back in.

fn main() {
    let mut factorial = 1_u64;

    for i in 2..100_000 {
        factorial = (factorial * i) % 1_000_000;
        while factorial % 10 == 0 {
            factorial /= 10;
        }
    }

    println!("{}", factorial);
}
