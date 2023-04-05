import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class CoveringSegments {
  private static class Segment {
    int start, end;

    Segment(int start, int end) {
      this.start = start;
      this.end = end;
    }
  }

  private static int[] optimalPoints(Segment[] segments) {
    List<Integer> points = new ArrayList<>();

    Arrays.sort(segments, (a, b) -> Integer.compare(a.end, b.end));

    while (segments.length > 0) {
      int point = segments[0].end;
      points.add(point);

      int i = 0;
      while (i < segments.length && segments[i].start <= point && segments[i].end >= point)
        i++;

      segments = Arrays.copyOfRange(segments, i, segments.length);
    }

    return points.stream().mapToInt(i -> i).toArray();
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int n = scanner.nextInt();
    Segment[] segments = new Segment[n];
    for (int i = 0; i < n; i++) {
      int start, end;
      start = scanner.nextInt();
      end = scanner.nextInt();
      segments[i] = new Segment(start, end);
    }
    scanner.close();

    int[] points = optimalPoints(segments);

    System.out.println(points.length);
    for (int point : points)
      System.out.print(point + " ");
  }
}
