import 'dart:io';
import 'dart:math';

final bool part1 = true;
final int N_ROUNDS = part1 ? 10 : inf;
final List<int> dx = [-1, -1, -1, 0, 0, 1, 1, 1];
final List<int> dy = [-1, 0, 1, -1, 1, -1, 0, 1];
final List<List<int>> dirGroups = [
  [0, 1, 2],
  [5, 6, 7],
  [0, 3, 5],
  [2, 4, 7]
];
final int inf = 1000000000;

Set<Point<int>> pos = {};

void main(List<String> arguments) {
  File file = File('input.txt');
  List<String> map = file.readAsLinesSync();
  for (int i = 0; i < map.length; ++i) {
    for (int j = 0; j < map[i].length; ++j) {
      if (map[i][j] == '#') {
        pos.add(Point(i, j));
      }
    }
  }

  for (int i = 0; i < N_ROUNDS; ++i) {
    Map<Point<int>, Point<int>> proposal = {};
    Map<Point<int>, int> cnt = {};
    pos.forEach((p) {
      List<bool> blocked = List.generate(
          8, (j) => pos.contains(Point(p.x + dx[j], p.y + dy[j])));
      if (blocked.indexWhere((element) => element) == -1) {
        return;
      }

      for (int j = 0; j < dirGroups.length; ++j) {
        if (dirGroups[j].indexWhere((element) => blocked[element]) == -1) {
          int d = dirGroups[j][1];
          Point<int> pro = Point(p.x + dx[d], p.y + dy[d]);
          proposal[p] = pro;
          cnt[pro] = (cnt[pro] ?? 0) + 1;
          break;
        }
      }
    });

    Set<Point<int>> newPos = pos
        .map((e) => proposal.containsKey(e) && cnt[proposal[e]!] == 1
            ? proposal[e]!
            : e)
        .toSet();
    if (newPos.difference(pos).length == 0) {
      print(i + 1);
      exit(0);
    }
    pos = newPos;

    var tmp = dirGroups[0];
    dirGroups.removeAt(0);
    dirGroups.add(tmp);
  }

  int minx = pos.fold<int>(inf, (minx, element) => min(minx, element.x));
  int maxx = pos.fold<int>(-inf, (maxx, element) => max(maxx, element.x));
  int miny = pos.fold<int>(inf, (miny, element) => min(miny, element.y));
  int maxy = pos.fold<int>(-inf, (maxy, element) => max(maxy, element.y));

  print((maxx - minx + 1) * (maxy - miny + 1) - pos.length);
}
