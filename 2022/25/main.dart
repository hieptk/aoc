import 'dart:io';

Map<String, int> val = {'=': -2, '-': -1, '0': 0, '1': 1, '2': 2};

Map<int, String> char = {-1: '-', -2: '='};

int decimal(String s) {
  int p = 1, res = 0;
  for (int i = s.length - 1; i >= 0; --i) {
    res += val[s[i]]! * p;
    p *= 5;
  }
  return res;
}

String snafu(int n) {
  String res = "";
  while (n > 0) {
    int x = n % 5;
    if (x < 3) {
      res += '$x';
    } else {
      res += char[x - 5]!;
      n += 5 - x;
    }
    n ~/= 5;
  }
  res = res.split('').reversed.join();
  return res;
}

void main(List<String> arguments) {
  File file = File('input.txt');
  int res =
      file.readAsLinesSync().map((e) => decimal(e)).reduce((a, b) => a + b);
  print(res);
  print(snafu(res));
}
