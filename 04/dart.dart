import 'dart:io';

void main(List<String> arguments) {
  File file = File('input.txt');
  int res = 0, res2 = 0;
  for (String line in file.readAsLinesSync()) {
    List<String> tokens = line.split(RegExp('[-,]'));
    assert(tokens.length == 4);
    List<int> arr = [];
    for (String t in tokens) {
      arr.add(int.parse(t));
    }
    if ((arr[0] <= arr[2] && arr[1] >= arr[3]) || (arr[2] <= arr[0] && arr[3] >= arr[1])) {
      res++;
    }
    if ((arr[0] > arr[3]) || (arr[1] < arr[2])) {
      continue;
    }
    res2++;
  }
  print(res);
  print(res2);
}
