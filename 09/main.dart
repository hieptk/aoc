import 'dart:io';

class Coord {
  int x;
  int y;

  @override
  bool operator==(Object other) {
    return other is Coord && other.x == x && other.y == y;
  }

  @override
  int get hashCode {
    return 0;
  }

  Coord(this.x, this.y);

  int sqDist(Coord other) {
    return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
  }

  void moveTowards(Coord other) {
    int dx = other.x - x;
    int dy = other.y - y;
    x += dx != 0 ? dx ~/ dx.abs() : 0;
    y += dy != 0 ? dy ~/ dy.abs() : 0;
  }
}

class Rope {
  List<Coord> knots;

  Rope(this.knots);

  Coord tail() {
    return knots.last;
  }

  void move(Coord dir) {
    knots.first.x += dir.x;
    knots.first.y += dir.y;
    for (int i = 1; i < knots.length; ++i) {
      if (knots[i].sqDist(knots[i - 1]) > 2) {
        knots[i].moveTowards(knots[i - 1]);
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
  // Rope rope = Rope(List.generate(2, (_) => Coord(0, 0)));

  // part 2
  Rope rope = Rope(List.generate(10, (_) => Coord(0, 0)));

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
