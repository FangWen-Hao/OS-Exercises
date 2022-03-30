int collatzConjecture(int n) {
    if ((n % 2) == 0) {
      // n= n/2,         if n is even
        return (n / 2);
    }
    else {
      // n= 3*n+1,     if n is odd
        return (3 * n + 1);
    }
}
