/// # How many double pandigital numbers are there?
///
///  There are 18! choices of picking a number. Half of these will
///  be duplicated since we can choose a number from one of two positions. So
///
///  18!/2 ~= 3.2x10^15
///
///  This seems slightly unreasonable to bruteforce, so we need to reduce
///  the search space somehow.
///
/// # Divisibility by 11 constraints
///
///  A number is divisible by 11 iff its alternating digit sum is divisible
///  by 11.
///
///  This reduces the search space a fair amount, as we can construct numbers
///  which only have this form.
