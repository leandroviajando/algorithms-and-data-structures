import java.util.Scanner;

public class LCM {
  private static long lcm_naive(int a, int b) {
    for (long l = 1; l <= (long) a * b; ++l)
      if (l % a == 0 && l % b == 0)
        return l;

    return (long) a * b;
  }

  private static int gcd(int a, int b) {
    int min = Math.min(a, b);
    int max = Math.max(a, b);

    return min == 0 ? max : gcd(max % min, min);
  }

  private static long lcm(int a, int b) {
    return (long) a * b / gcd(a, b);
  }

  public static void main(String args[]) {
    Scanner scanner = new Scanner(System.in);
    int a = scanner.nextInt();
    int b = scanner.nextInt();
    scanner.close();

    System.out.println(lcm(a, b));
    System.out.println(lcm_naive(a, b));
  }
}
