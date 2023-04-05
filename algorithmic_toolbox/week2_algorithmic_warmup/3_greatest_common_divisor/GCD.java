import java.util.Scanner;

public class GCD {
  private static int gcd_naive(int a, int b) {
    int current_gcd = 1;

    for (int d = 2; d <= a && d <= b; ++d)
      if (a % d == 0 && b % d == 0)
        if (d > current_gcd)
          current_gcd = d;

    return current_gcd;
  }

  private static int gcd_euclidean(int a, int b) {
    int min = Math.min(a, b);
    int max = Math.max(a, b);

    return min == 0 ? max : gcd_euclidean(max % min, min);
  }

  public static void main(String args[]) {
    Scanner scanner = new Scanner(System.in);
    int a = scanner.nextInt();
    int b = scanner.nextInt();
    scanner.close();

    System.out.println(gcd_naive(a, b));
    System.out.println(gcd_euclidean(a, b));
  }
}
