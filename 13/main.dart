import 'dart:io';
import 'dart:math';
import 'dart:convert';

int compare(dynamic a, dynamic b) {
  if (a is int) {
    if (b is int) {
      return a.compareTo(b);
    }
    return compare([a], b);
  }
  if (b is int) {
    return compare(a, [b]);
  }
  if (a is List && b is List) {
    int n = min(a.length, b.length);
    for (int i = 0; i < n; ++i) {
      int tmp = compare(a[i], b[i]);
      if (tmp != 0) {
        return tmp;
      }
    }
    return a.length.compareTo(b.length);
  }
  throw Exception('Wrong!');
}

void main(List<String> arguments) {
  File file = File('input.txt');
  List<String> lines = file.readAsLinesSync();
  List<dynamic> packets = [];
  int res = 0;
  for (int i = 0; i + 1 < lines.length; i += 3) {
    dynamic a = json.decode(lines[i]);
    dynamic b = json.decode(lines[i + 1]);
    packets.add(a);
    packets.add(b);
    if (compare(a, b) < 0) {
      res += i ~/ 3 + 1;
    }
  }
  print(res);

  packets.add([
    [2]
  ]);
  packets.add([
    [6]
  ]);
  packets.sort(compare);

  for (int i = 0; i < packets.length; ++i) {
    if (jsonEncode(packets[i]) == '[[2]]' ||
        jsonEncode(packets[i]) == '[[6]]') {
      print(i + 1);
    }
  }
}
