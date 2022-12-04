import 'dart:io';

void main(List<String> arguments) {
  File file = File('input.txt');
  int res = 0, res2 = 0;
  for (String line in file.readAsLinesSync()) {
    List<int> arr = line.split(RegExp('[,-]')).map((e) => int.parse(e)).toList();
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
