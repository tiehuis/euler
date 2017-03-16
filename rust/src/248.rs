/// 13! = 2^10 * 3^5 * 5^2 * 7 * 11 * 13
///
/// phi(p^k) = p^k - p^(k-1) must be contained within the specified factors
///
/// This in effect is a counting problem using available phi values that are
/// known to generate the specified function. We need to determine how we
/// produce values in order.
