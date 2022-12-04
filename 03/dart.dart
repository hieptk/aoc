import 'dart:io';

int id(int x) {
  if (x >= 97) {
    return x - 97;
  }
  return x - 39;
}

bool bit(int n, int i) {
  return ((n >> i) & 1) > 0;
}

void main(List<String> arguments) {
  File file = File('input.txt');
  int res = 0, res2 = 0;
  int lineNum = 0;
  List cntLines = [0, 0, 0];
  for (String line in file.readAsLinesSync()) {
    lineNum++;
    int cnt = 0;
    for (int i = 0; i < line.length / 2; ++i) {
      cnt |= 1 << id(line.codeUnitAt(i));
    }
    for (int i = line.length ~/ 2; i < line.length; ++i) {
      if (bit(cnt, id(line.codeUnitAt(i)))) {
        res += id(line.codeUnitAt(i)) + 1;
        break;
      }
    }

    // part 2
    for (int x in line.codeUnits) {
      cntLines[lineNum % 3] |= 1 << id(x);
    }
    if (lineNum % 3 == 0) {
      int intersect = cntLines[0] & cntLines[1] & cntLines[2];
      for (int i = 0; i < 52; ++i) {
        if (bit(intersect, i)) {
          res2 += i + 1;
          break;
        }
      }
      cntLines = [0, 0, 0];
    }
  }
  print(res);
  print(res2);
}
