import 'dart:collection';
import 'dart:io';
import 'dart:math';

final bool part2 = true;
final int inf = 1000000000;
final List<Point<int>> dir = [
  Point(-1, 0),
  Point(0, 1),
  Point(1, 0),
  Point(0, -1)
];

int height(Point<int> a, List<String> map) {
  if (map[a.x][a.y] == 'S') {
    return 0;
  } else if (map[a.x][a.y] == 'E') {
    return 25;
  } else {
    return map[a.x].codeUnitAt(a.y) - 97;
  }
}

void main(List<String> arguments) {
  File file = File('input.txt');
  List<String> map = file.readAsLinesSync();
  int m = map.length, n = map[0].length;

  List<List<int>> dist = List.generate(m, (index) => List.filled(n, inf));
  Queue<Point<int>> q = Queue();
  int ex = -1, ey = -1;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (map[i][j] == 'S' || (part2 && map[i][j] == 'a')) {
        dist[i][j] = 0;
        q.addLast(Point<int>(i, j));
      } else if (map[i][j] == 'E') {
        ex = i;
        ey = j;
      }
    }
  }

  while (q.isNotEmpty) {
    Point<int> a = q.removeFirst();
    dir.forEach((d) {
      Point<int> b = Point(a.x + d.x, a.y + d.y);
      if (b.x >= 0 &&
          b.x < m &&
          b.y >= 0 &&
          b.y < n &&
          height(a, map) + 1 >= height(b, map) &&
          dist[b.x][b.y] > dist[a.x][a.y] + 1) {
        dist[b.x][b.y] = dist[a.x][a.y] + 1;
        q.addLast(b);
      }
    });
  }

  print(dist[ex][ey]);
}
