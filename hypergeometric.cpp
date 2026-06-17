//double hypergeometricPMF(int N, int K, int n, int x) {
//	// P(X=x) = C(K,x)*C(N-K,n-x) / C(N,n)
//	return (combinations_stable(K, x) * combinations_stable(N - K, n - x))
//		/ combinations_stable(N, n);
//}
//
//double hypergeometricExpected(int N, int K, int n) {
//	return (double)n * K / N;  // = 0.6
//}
//
//double hypergeometricVariance(int N, int K, int n) {
//	double p = (double)K / N;
//	return n * p * (1 - p) * ((double)(N - n) / (N - 1));  // = 0.4421
//}
