import java.util.Scanner;

class APlusB {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int a = scanner.nextInt();
    int b = scanner.nextInt();
    scanner.close();
    int sum = a + b;
    System.out.println(sum);
  }
}
