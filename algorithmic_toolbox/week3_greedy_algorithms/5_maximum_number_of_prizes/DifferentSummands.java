import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class DifferentSummands {
  private static List<Integer> optimalSummands(int n) {
    List<Integer> summands = new ArrayList<Integer>();

    for (int i = 1; i <= n; i++) {
      if (n - i > i) {
        summands.add(i);
        n -= i;
      } else {
        summands.add(n);
        break;
      }
    }

    return summands;
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int n = scanner.nextInt();
    scanner.close();

    List<Integer> summands = optimalSummands(n);

    System.out.println(summands.size());
    for (Integer summand : summands)
      System.out.print(summand + " ");
  }
}
