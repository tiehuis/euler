extern crate primal;

fn main() {
    let s = primal::Sieve::new(100000);
    let f = s.factor(600851475143).unwrap();
    println!("{}", f.iter().last().unwrap().0)
}
