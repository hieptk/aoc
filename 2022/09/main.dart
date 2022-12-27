import 'dart:io';
import 'dart:math';

class Coord extends Point<int> {
  Coord(int x, int y) : super(x, y);

  Coord moveDir(Coord dir) {
    return Coord(x + dir.x, y + dir.y);
  }

  Coord moveTowards(Coord other) {
    int dx = other.x - x;
    int dy = other.y - y;
    return Coord(
        x + (dx != 0 ? dx ~/ dx.abs() : 0), y + (dy != 0 ? dy ~/ dy.abs() : 0));
  }
}

class Rope {
  List<Coord> knots;

  Rope(int n): this.knots = List.generate(n, (_) => Coord(0, 0));

  Coord tail() {
    return knots.last;
  }

  void move(Coord dir) {
    knots.first = knots.first.moveDir(dir);
    for (int i = 1; i < knots.length; ++i) {
      if (knots[i].squaredDistanceTo(knots[i - 1]) > 2) {
        knots[i] = knots[i].moveTowards(knots[i - 1]);
      }
    }
  }
}

void main(List<String> arguments) {
  File file = File('input.txt');

  Map<String, Coord> dir = {
    'U': Coord(0, 1),
    'D': Coord(0, -1),
    'L': Coord(-1, 0),
    'R': Coord(1, 0)
  };

  // part 1
  // Rope rope = Rope(2);

  // part 2
  Rope rope = Rope(10);

  Set<Coord> visited = {Coord(0, 0)};

  for (String line in file.readAsLinesSync()) {
    List<String> tokens = line.split(' ');
    int n = int.parse(tokens[1]);
    Coord d = dir[tokens[0]]!;
    for (int i = 1; i <= n; ++i) {
      rope.move(d);
      visited.add(Coord(rope.tail().x, rope.tail().y));
    }
  }

  print(visited.length);
}
