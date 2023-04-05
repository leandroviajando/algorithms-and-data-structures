import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

class Item {
  public int weight;
  public int value;
  public double unitValue;
}

public class FractionalKnapsack {
  private static double getOptimalValue(int capacity, int[] values, int[] weights) {
    int weight = 0;
    double value = 0.0;

    List<Item> items = new ArrayList<>();
    for (int i = 0; i < weights.length; i++) {
      Item item = new Item();
      item.weight = weights[i];
      item.value = values[i];
      item.unitValue = (double) values[i] / weights[i];
      items.add(item);
    }

    Collections.sort(items, (a, b) -> Double.compare(a.unitValue, b.unitValue));
    Collections.reverse(items);

    for (Item item : items) {
      if (weight >= capacity)
        break;

      int units = Math.min(item.weight, capacity - weight);
      weight += units;
      value += units * item.unitValue;
    }

    return value;
  }

  public static void main(String args[]) {
    Scanner scanner = new Scanner(System.in);
    int n = scanner.nextInt();
    int capacity = scanner.nextInt();
    int[] values = new int[n];
    int[] weights = new int[n];
    for (int i = 0; i < n; i++) {
      values[i] = scanner.nextInt();
      weights[i] = scanner.nextInt();
    }
    scanner.close();

    System.out.println(getOptimalValue(capacity, values, weights));
  }
}
