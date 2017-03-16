/// Instead of dealing with big integers, we compute the lower portion
/// of fib(n) and then use a variation of binets formula to calculate the
/// topmost 10 digits.

fn is_pandigital(n: u64) -> bool {
    let mut seen = [false; 9];
    let mut n = n;
    let mut c = 0;

    while n != 0 {
        c += 1;
        let index = (n % 10) as usize;
        if index == 0 || seen[index - 1] == true {
            return false;
        } else {
            seen[index - 1] = true;
        }
        n /= 10;
    }

    c == 9
}

fn main() {
    let mut k = 2_u64;
    let mut fc = 1_u64;
    let mut fl = 1_u64;

    let log_phi: f64 = ((1_f64 + 5_f64.sqrt()) / 2_f64).log10();
    let log_sqrt5: f64 = 5_f64.sqrt().log10();

    loop {
        k += 1;
        let t = fc;
        fc = (fc + fl) % 1_000_000_000;
        fl = t;

        if is_pandigital(fc) {
            // Fn = round(phi^n / sqrt(5))
            // log10(Fn) = n*log10(phi^n) - log10(sqrt(5))
            // top10(Fn) = floor(10^(8 + log10(Fn) - floor(log10(Fn))))

            let v = k as f64 * log_phi - log_sqrt5;
            let tc = 10_f64.powf(8_f64 + v - v.floor()).floor() as u64;

            if is_pandigital(tc) {
                println!("{}", k);
                break;
            }
        }
    }
}
