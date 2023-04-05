import java.util.Arrays;
import java.util.Scanner;

public class LargestNumber {
  private static int compare(String a, String b) {
    String ab = a + b;
    String ba = b + a;
    return ba.compareTo(ab);
  }

  public static String largestNumber(String[] a) {
    Arrays.sort(a, (x, y) -> compare(x, y));

    String result = "";
    for (int i = 0; i < a.length; i++)
      result += a[i];
    return result;
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int n = scanner.nextInt();
    String[] a = new String[n];
    for (int i = 0; i < n; i++)
      a[i] = scanner.next();
    scanner.close();

    System.out.println(largestNumber(a));
  }
}
