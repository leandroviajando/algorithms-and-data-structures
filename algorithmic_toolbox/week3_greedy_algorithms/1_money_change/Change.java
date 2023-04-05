import java.util.Scanner;

public class Change {
  private static int getChange(int m) {
    int n = m % 10, o = n % 5;

    return m / 10 + n / 5 + o / 1;
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int m = scanner.nextInt();
    scanner.close();

    System.out.println(getChange(m));
  }
}
