import 'dart:collection';
import 'dart:io';

final bool part1 = false;
final int N_ROUNDS = part1 ? 20 : 10000;
final int mod = 9699690;

class Monkey {
  final Queue<int> items;
  final String op;
  final int opVal;
  final int testVal;
  final int trueThrow, falseThrow;

  Monkey(this.items, this.op, this.opVal, this.testVal, this.trueThrow,
      this.falseThrow);

  void doMonkeyThing(List<Monkey> monkeys) {
    while (items.isNotEmpty) {
      int x = items.removeFirst();
      if (op == '+') {
        x = (x + opVal) % mod;
      } else if (op == '*') {
        x = (x * opVal) % mod;
      } else {
        x = (x * x) % mod;
      }
      if (part1) {
        x ~/= 3;
      }
      if (x % testVal == 0) {
        monkeys[trueThrow].items.addLast(x);
      } else {
        monkeys[falseThrow].items.addLast(x);
      }
    }
  }
}

void main(List<String> arguments) {
  File file = File('input.txt');
  List<String> lines = file.readAsLinesSync();
  List<Monkey> monkeys = [];
  for (int i = 0; i + 5 < lines.length; i += 7) {
    Queue<int> items = Queue.from(lines[i + 1]
        .trimLeft()
        .split(' ')
        .sublist(2)
        .map((e) => int.parse(e.replaceAll(',', ''))));
    List<String> tmp = lines[i + 2].trimLeft().split(' ');
    String op = '';
    int opVal = 1;
    if (tmp.last != 'old') {
      op = tmp[4];
      opVal = int.parse(tmp.last);
    } else {
      // old * old
      op = '^';
      opVal = 2;
    }
    int testVal = int.parse(lines[i + 3].split(' ').last);
    int trueThrow = int.parse(lines[i + 4].split(' ').last);
    int falseThrow = int.parse(lines[i + 5].split(' ').last);
    monkeys.add(Monkey(items, op, opVal, testVal, trueThrow, falseThrow));
  }

  List<int> cnt = List.filled(monkeys.length, 0);
  for (int i = 1; i <= N_ROUNDS; ++i) {
    for (int j = 0; j < monkeys.length; ++j) {
      cnt[j] += monkeys[j].items.length;
      monkeys[j].doMonkeyThing(monkeys);
    }
  }

  print(cnt);
  cnt.sort();
  print(cnt.last * cnt[cnt.length - 2]);
}
