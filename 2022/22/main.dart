import 'dart:io';

final bool part1 = false;
final RegExp numExp = RegExp(r'[0-9]+');
final RegExp dirExp = RegExp(r'[LR]');
final List<int> dx = [0, 1, 0, -1];
final List<int> dy = [1, 0, -1, 0];
final int CUBE_SZ = 50;

class State {
  final int x, y, d;

  State(this.x, this.y, this.d);
}

late List<String> map;
late List<int> steps;
late List<String> dir;
late List<int> l, r, up, down;

State moveOne(State cur) {
  int i2 = cur.x + dx[cur.d], j2 = cur.y + dy[cur.d];
  if (i2 > down[cur.y]) {
    i2 = up[cur.y];
  } else if (i2 < up[cur.y]) {
    i2 = down[cur.y];
  }
  if (j2 < l[cur.x]) {
    j2 = r[cur.x];
  } else if (j2 > r[cur.x]) {
    j2 = l[cur.x];
  }
  return State(i2, j2, cur.d);
}

int getSide(State cur) {
  if (cur.x < CUBE_SZ) {
    return cur.y ~/ CUBE_SZ;
  }
  if (cur.x < 2 * CUBE_SZ) {
    return 3;
  }
  if (cur.x < 3 * CUBE_SZ) {
    return cur.y ~/ CUBE_SZ + 4;
  }
  return 6;
}

State moveOnePart2(State cur) {
  if (cur.x + dx[cur.d] >= up[cur.y] &&
      cur.x + dx[cur.d] <= down[cur.y] &&
      cur.y + dy[cur.d] >= l[cur.x] &&
      cur.y + dy[cur.d] <= r[cur.x]) {
    return State(cur.x + dx[cur.d], cur.y + dy[cur.d], cur.d);
  }
  int side = getSide(cur);
  switch (side) {
    case 1:
      return cur.d == 2
          ? State(3 * CUBE_SZ - 1 - cur.x, 0, 0)
          : State(cur.y + 2 * CUBE_SZ, 0, 0); // d == 3
    case 2:
      switch (cur.d) {
        case 0:
          return State(3 * CUBE_SZ - 1 - cur.x, 2 * CUBE_SZ - 1, 2);
        case 1:
          return State(cur.y - CUBE_SZ, 2 * CUBE_SZ - 1, 2);
        case 3:
          return State(4 * CUBE_SZ - 1, cur.y - 2 * CUBE_SZ, 3);
      }
      throw Exception();
    case 3:
      return cur.d == 0
          ? State(CUBE_SZ - 1, cur.x + CUBE_SZ, 3)
          : State(2 * CUBE_SZ, cur.x - CUBE_SZ, 1); // d == 2
    case 4:
      return cur.d == 2
          ? State(3 * CUBE_SZ - 1 - cur.x, CUBE_SZ, 0)
          : State(cur.y + CUBE_SZ, CUBE_SZ, 0); // d == 3
    case 5:
      return cur.d == 0
          ? State(3 * CUBE_SZ - 1 - cur.x, 3 * CUBE_SZ - 1, 2)
          : State(cur.y + 2 * CUBE_SZ, CUBE_SZ - 1, 2); // d == 1
    default:
      switch (cur.d) {
        case 0:
          return State(3 * CUBE_SZ - 1, cur.x - 2 * CUBE_SZ, 3);
        case 1:
          return State(0, cur.y + 2 * CUBE_SZ, 1);
        case 2:
          return State(0, cur.x - 2 * CUBE_SZ, 1);
      }
      throw Exception();
  }
}

State move(State cur, int step) {
  for (int k = 0; k < step; ++k) {
    State next = part1 ? moveOne(cur) : moveOnePart2(cur);
    if (map[next.x][next.y] == '#') {
      break;
    }
    cur = next;
  }
  return cur;
}

void main(List<String> arguments) {
  File file = File('input.txt');
  List<String> lines = file.readAsLinesSync();
  map = lines.sublist(0, lines.length - 2);
  steps =
      numExp.allMatches(lines.last).map((e) => int.parse(e.group(0)!)).toList();
  dir = dirExp.allMatches(lines.last).map((e) => e.group(0)!).toList();

  l = map
      .map((e) => e.split('').indexWhere((element) => element != ' '))
      .toList();
  r = map.map((e) => e.length - 1).toList();
  up = [];
  down = [];
  for (int i = 0; i < 3 * CUBE_SZ; ++i) {
    up.add(map
        .indexWhere((element) => element.length >= i + 1 && element[i] != ' '));
    down.add(map.lastIndexWhere(
        (element) => element.length >= i + 1 && element[i] != ' '));
  }

  State cur = State(0, l[0], 0);
  cur = move(cur, steps[0]);

  for (int i = 0; i < dir.length; ++i) {
    if (dir[i] == 'L') {
      cur = State(cur.x, cur.y, (cur.d + 3) % 4);
    } else {
      cur = State(cur.x, cur.y, (cur.d + 1) % 4);
    }
    cur = move(cur, steps[i + 1]);
  }
  print(1000 * (cur.x + 1) + 4 * (cur.y + 1) + cur.d);
}
