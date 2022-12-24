import 'dart:collection';
import 'dart:io';
import 'dart:math';

final List<int> dx = [-1, 0, 1, 0, 0];
final List<int> dy = [0, 1, 0, -1, 0];
final Map<String, int> dirId = {'^': 0, '>': 1, 'v': 2, '<': 3};
final String dirChar = '^>v<';

class Tuple {
  final int x, y, t;

  Tuple(this.x, this.y, this.t);

  @override
  bool operator ==(Object other) =>
      other is Tuple && other.x == x && other.y == y && other.t == t;

  int get hashCode => Object.hash(x, y, t);
}

late List<String> map;
late int m, n;
List<Tuple> pos = [];
Map<int, Set<Point<int>>> posCache = {};

Point<int> move(Tuple cur, int step) {
  return Point(((cur.x + dx[cur.t] * step - 1) % (m - 2) + m - 2) % (m - 2) + 1,
      ((cur.y + dy[cur.t] * step - 1) % (n - 2) + n - 2) % (n - 2) + 1);
}

int bfs(int u0, int v0, int t0, int u, int v) {
  Queue<Tuple> q = Queue.from([Tuple(u0, v0, t0)]);
  Set<Tuple> visited = {};
  while (q.isNotEmpty) {
    Tuple st = q.removeFirst();
    posCache.putIfAbsent(
        st.t + 1, () => (pos.map((e) => move(e, st.t + 1)).toSet()));
    Set<Point<int>> snowPos = posCache[st.t + 1]!;
    for (int i = 0; i < 5; ++i) {
      int i2 = st.x + dx[i], j2 = st.y + dy[i];
      Tuple st2 = Tuple(i2, j2, st.t + 1);
      if (i2 >= 0 &&
          i2 < m &&
          map[i2][j2] != '#' &&
          !snowPos.contains(Point(i2, j2)) &&
          !visited.contains(st2)) {
        if (i2 == u && j2 == v) {
          return st.t + 1;
        }
        visited.add(st2);
        q.addLast(st2);
      }
    }
  }
  return -1;
}

void main(List<String> arguments) {
  File file = File('input.txt');
  map = file.readAsLinesSync();
  m = map.length;
  n = map[0].length;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (dirId.containsKey(map[i][j])) {
        pos.add(Tuple(i, j, dirId[map[i][j]]!));
      }
    }
  }

  int part1 = bfs(0, 1, 0, m - 1, n - 2);
  print(part1);

  int part2 = bfs(m - 1, n - 2, part1, 0, 1);
  part2 = bfs(0, 1, part2, m - 1, n - 2);
  print(part2);
}
