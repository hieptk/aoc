import 'dart:io';

void main(List<String> arguments) {
  List<String> arr = [
    "SCVN",
    "ZMJHNS",
    "MCTGJND",
    "TDFJWRM",
    "PFH",
    "CTZHJ",
    "DPRQFSLZ",
    "CSLHDFPW",
    "DSMPFNGZ"
  ];
  File file = File('input.txt');
  for (String line in file.readAsLinesSync()) {
    List<String> tokens = line.split(' ');
    int n = int.parse(tokens[1]);
    int from = int.parse(tokens[3]) - 1;
    int to = int.parse(tokens[5]) - 1;
    // part 1
    // String moved = arr[from].substring(arr[from].length - n).split('').reversed.join();
    // part 2
    String moved = arr[from].substring(arr[from].length - n);
    arr[to] += moved;
    arr[from] = arr[from].substring(0, arr[from].length - n);
  }
  String res = arr.map((e) => e[e.length - 1]).join();
  print(res);
}
