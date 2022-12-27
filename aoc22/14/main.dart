import 'dart:io';
import 'dart:math';

final bool part1 = false;
final int inf = 1000;
final List<int> dx = [0, -1, 1];

void draw(int x0, int y0, int x1, int y1, List<List<String>> map) {
  if (x0 == -1) {
    map[y1][x1] = '#';
    return;
  }
  if (x0 == x1) {
    if (y0 > y1) {
      int tmp = y0;
      y0 = y1;
      y1 = tmp;
    }
    for (int y = y0; y <= y1; ++y) {
      map[y][x0] = '#';
    }
    return;
  }
  if (x0 > x1) {
    int tmp = x0;
    x0 = x1;
    x1 = tmp;
  }
  for (int x = x0; x <= x1; ++x) {
    map[y0][x] = '#';
  }
}

void main(List<String> arguments) {
  File file = File('input.txt');
  List<List<String>> map = List.generate(inf, (_) => List.filled(inf, '.'));
  int maxy = -1;
  for (String line in file.readAsLinesSync()) {
    int prevx = -1, prevy = -1;
    for (String token in line.split('->')) {
      List<String> coord = token.trim().split(',');
      int x = int.parse(coord[0]);
      int y = int.parse(coord[1]);
      draw(prevx, prevy, x, y, map);
      prevx = x;
      prevy = y;
      maxy = max(maxy, y);
    }
  }

  if (!part1) {
    for (int x = 0; x < inf; ++x) {
      map[maxy + 2][x] = '#';
    }
    maxy += 2;
  }

  int res = 0;
  while (true) {
    int x = 500, y = 0;
    while (true) {
      bool rest = true;
      for (int i = 0; i < 3; ++i) {
        if (map[y + 1][x + dx[i]] == '.') {
          y++;
          x += dx[i];
          rest = false;
          break;
        }
      }
      if (rest || y > maxy) {
        break;
      }
    }
    if (y > maxy) {
      break;
    }
    map[y][x] = 'o';
    res++;
    if (!part1 && x == 500 && y == 0) {
      break;
    }
  }

  print(res);
}
