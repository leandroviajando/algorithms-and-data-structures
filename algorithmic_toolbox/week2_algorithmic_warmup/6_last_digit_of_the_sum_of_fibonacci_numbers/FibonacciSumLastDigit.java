import java.util.Scanner;

public class FibonacciSumLastDigit {
  private static long getFibonacciSumNaive(long n) {
    if (n <= 1)
      return n;

    long previous = 0;
    long current = 1;
    long sum = 1;

    for (long i = 0; i < n - 1; ++i) {
      long tmp_previous = previous;
      previous = current;
      current = tmp_previous + current;
      sum += current;
    }

    return sum % 10;
  }

  /*
   * The last digit of the numbers in the Fibonacci Sequence form a pattern that
   * repeats after
   * every 60th number. Source:
   * https://www.goldennumber.net/fibonacci-60-repeating-pattern/
   */
  private static long getFibonacciSum(long n) {
    return getFibonacciSumNaive(n % 60);
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    long n = scanner.nextLong();
    scanner.close();

    System.out.println(getFibonacciSum(n));
    System.out.println(getFibonacciSumNaive(n));
  }
}
