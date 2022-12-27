import 'dart:io';

void main(List<String> arguments) {
  File file = File('input.txt');
  int res = 0, res2 = 0;
  for (String line in file.readAsLinesSync()) {
    int x = line.codeUnitAt(0) - 'A'.codeUnitAt(0);
    int y = line.codeUnitAt(2) - 'X'.codeUnitAt(0);
    res += y + 1;
    if (x == y) {
      res += 3;
    } else if ((x + 1) % 3 == y) {
      res += 6;
    }
    if (y == 0) {
      res2 += (x + 2) % 3 + 1;
    } else if (y == 1) {
      res2 += x + 4;
    } else {
      res2 += (x + 1) % 3 + 7;
    }
  }
  print(res);
  print(res2);
}
