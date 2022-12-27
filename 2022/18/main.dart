import 'dart:collection';
import 'dart:io';

class Point {
  int x, y, z;

  Point(this.x, this.y, this.z);
}

final bool part2 = true;
final int nm = 22;
final List<int> dx = [-1, 0, 0, 0, 0, 1];
final List<int> dy = [0, -1, 0, 0, 1, 0];
final List<int> dz = [0, 0, -1, 1, 0, 0];

List<List<List<bool>>> mark = List.generate(nm, (_) => List.generate(nm, (_) => List.filled(nm, false)));
List<List<List<bool>>> visited = List.generate(nm, (_) => List.generate(nm, (_) => List.filled(nm, false)));
List<Point> points = [];

void main(List<String> arguments) {
  File file = File('input.txt');
  for (String line in file.readAsLinesSync()) {
    List<int> coord = line.split(',').map((e) => int.parse(e) + 1).toList();
    mark[coord[0]][coord[1]][coord[2]] = true;
    points.add(Point(coord[0], coord[1], coord[2]));
  }

  // part 1 - solution 1
  int res = 0;
  points.forEach((p) {
    for (int d = 0; d < 6; ++d) {
      if (!mark[p.x + dx[d]][p.y + dy[d]][p.z + dz[d]]) {
        res++;
      }
    }
  });
  print(res);

  // part 2/part 1 - solution 2
  Queue<Point> q = Queue();
  if (!part2) { // part 1 solution 2
    for (int i = 0; i < nm; ++i) {
      for (int j = 0; j < nm; ++j) {
        for (int k = 0; k < nm; ++k) {
          if (!mark[i][j][k]) {
            q.add(Point(i, j, k));
            visited[i][j][k] = true;
          }
        }
      }
    }
  } else {
    for (int i = 0; i < nm; ++i) {
      for (int j = 0; j < nm; ++j) {
        q.addAll([Point(i, j, 0), Point(i, 0, j), Point(0, i, j)]);
        visited[i][j][0] = visited[i][0][j] = visited[0][i][j] = true;
      }
    }
  }

  int res2 = 0;
  while (q.isNotEmpty) {
    Point e = q.removeFirst();
    for (int d = 0; d < 6; ++d) {
      Point e2 = Point(e.x + dx[d], e.y + dy[d], e.z + dz[d]);
      if (e2.x < 0 || e2.x >= nm || e2.y < 0 || e2.y >= nm || e2.z < 0 || e2.z >= nm) {
        continue;
      }
      if (mark[e2.x][e2.y][e2.z]) {
        res2++;
        continue;
      }
      if (!visited[e2.x][e2.y][e2.z]) {
        visited[e2.x][e2.y][e2.z] = true;
        q.addLast(e2);
      }
    }
  }
  print(res2);
}
