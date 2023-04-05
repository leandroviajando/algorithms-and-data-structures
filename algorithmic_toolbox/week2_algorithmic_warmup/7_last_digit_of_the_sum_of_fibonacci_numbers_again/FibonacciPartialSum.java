import java.util.Scanner;

public class FibonacciPartialSum {
  private static long getFibonacciPartialSumNaive(long from, long to) {
    long sum = 0;

    long current = 0, next = 1;

    for (long i = 0; i <= to; ++i) {
      if (i >= from)
        sum += current;

      long new_current = next;
      next = next + current;
      current = new_current;
    }

    return sum % 10;
  }

  private static final int PISANO_PERIOD = 60;

  /*
   * The last digit of the numbers in the Fibonacci Sequence form a pattern that
   * repeats after
   * every 60th number. Source:
   * https://www.goldennumber.net/fibonacci-60-repeating-pattern/
   */
  private static long getFibonacciPartialSum(long from, long to) {
    long[] fibNums = new long[PISANO_PERIOD];
    fibNums[0] = 0;
    fibNums[1] = 1;

    for (int i = 2; i <= PISANO_PERIOD; i++)
      fibNums[i] = fibNums[i - 1] + fibNums[i - 2];

    from %= PISANO_PERIOD;
    to %= PISANO_PERIOD;

    long sum = 0;
    for (long j = from; j <= to; j++) {
      sum += fibNums[(int) j % PISANO_PERIOD];
      sum %= 10;
    }

    return sum;
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    long from = scanner.nextLong();
    long to = scanner.nextLong();
    scanner.close();

    System.out.println(getFibonacciPartialSum(from, to));
    System.out.println(getFibonacciPartialSumNaive(from, to));
  }
}
