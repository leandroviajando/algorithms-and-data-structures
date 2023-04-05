#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;

  std::sort(segments.begin(), segments.end(), [](Segment a, Segment b) {
    return a.end < b.end;
  });

  while (segments.size() > 0) {
    int point = segments[0].end;
    points.push_back(point);

    for (size_t i = 0; i < segments.size(); ++i) {
      if (segments[i].start <= point && point <= segments[i].end) {
        segments.erase(segments.begin() + i);
        --i;
      }
    }
  }

  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i)
    std::cin >> segments[i].start >> segments[i].end;
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << std::endl;
  for (size_t i = 0; i < points.size(); ++i)
    std::cout << points[i] << " ";
}
