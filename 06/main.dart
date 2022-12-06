import 'dart:io';

void main(List<String> arguments) {
  File file = File('input.txt');
  String s = file.readAsStringSync();
  // part 1
  // int markerLen = 4;
  // part 2
  int markerLen = 14;
  for (int i = 0; i + markerLen - 1 < s.length; ++i) {
    if (Set.from(s.substring(i, i + markerLen).split('')).length == markerLen) {
      print(i + markerLen);
      break;
    }
  }
}
