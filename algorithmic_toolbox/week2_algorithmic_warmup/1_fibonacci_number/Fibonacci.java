import java.util.Scanner;

public class Fibonacci {
  public static long calcFibNaive(int n) {
    return n <= 1 ? n : calcFibNaive(n - 1) + calcFibNaive(n - 2);
  }

  public static long calcFibFast(int n) {
    if (n <= 1)
      return n;

    long[] fibNums = new long[n + 1];
    fibNums[0] = 0;
    fibNums[1] = 1;

    for (int i = 2; i <= n; i++)
      fibNums[i] = fibNums[i - 1] + fibNums[i - 2];

    return fibNums[n];
  }

  public static void main(String args[]) {
    Scanner scanner = new Scanner(System.in);
    int n = scanner.nextInt();
    scanner.close();

    System.out.println(calcFibFast(n));
  }
}
