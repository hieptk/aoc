import 'dart:io';
import 'dart:math';

final int n = 1000000000000;

List<List<String>> pieces = [
  ['####'],
  ['.#.', '###', '.#.'],
  ['..#', '..#', '###'],
  ['#', '#', '#', '#'],
  ['##', '##'],
];

List<List<String>> res = [];
late List<List<Point<int>>> seen;

bool checkMove(int x, int y, int dx, int dy, List<String> p) {
  if (x + dx < 0 || x + p[0].length - 1 + dx >= res[0].length || y + dy < 0) {
    return false;
  }
  for (int i = 0; i < p.length; ++i) {
    for (int j = 0; j < p[i].length; ++j) {
      if (p[i][j] == '#' && res[y + p.length - i - 1 + dy][x + j + dx] == '#') {
        return false;
      }
    }
  }
  return true;
}

void checkRepeated(int i, int t, int h) {
  if (seen[i % 5][t].x != -1) {
    int period = i - seen[i % 5][t].x;
    if ((n - i) % period == 0) {
      int step = h + 1 - seen[i % 5][t].y;
      print((n - i) ~/ period * step + h + 1);
      exit(0);
    }
  } else {
    seen[i % 5][t] = Point(i, h + 1);
  }
}

void main(List<String> arguments) {
  File file = File('input.txt');
  String push = file.readAsStringSync();
  seen = List.generate(5, (_) => List.filled(push.length, Point(-1, -1)));
  int h = -1, t = -1;

  for (int i = 0; i < n; ++i) {
    int x = 2, y = h + 4;
    List<String> p = pieces[i % pieces.length];
    while (res.length < y + p.length) {
      res.add('.......'.split(''));
    }

    while (true) {
      t = (t + 1) % push.length;
      checkRepeated(i, t, h);

      String d = push.substring(t, t + 1);
      int dx = (d == '<' ? -1 : 1);
      if (checkMove(x, y, dx, 0, p)) {
        x += dx;
      }

      if (!checkMove(x, y, 0, -1, p)) {
        break;
      }
      y--;
    }

    for (int i = 0; i < p.length; ++i) {
      for (int j = 0; j < p[i].length; ++j) {
        if (p[i][j] == '#') {
          res[y + p.length - i - 1][x + j] = '#';
        }
      }
    }

    h = max(h, y + p.length - 1);
  }

  print(h + 1);
}
