import 'dart:io';

int sum = 0, t = 0, x = 1;
List<List<String>> res = List.generate(6, (_) => List.filled(40, '.'));

void tick() {
  if (t % 40 >= x - 1 && t % 40 <= x + 1) {
    res[t ~/ 40][t % 40] = '#';
  }
  t++;
  if (t % 40 == 20) {
    sum += t * x;
  }
}

void main(List<String> arguments) {
  File file = File('input.txt');

  for (String line in file.readAsLinesSync()) {
    if (line == 'noop') {
      tick();
    } else {
      tick();
      tick();
      x += int.parse(line.split(' ')[1]);
    }
  }
  print(sum);
  for (List<String> line in res) {
    print(line.join());
  }
}
