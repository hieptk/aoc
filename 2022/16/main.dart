import 'dart:io';
import 'dart:math';

final RegExp numExp = RegExp(r'-?[0-9]+');

late List<List<List<int>>> dp;
Map<String, int> id = {};
int nNodes = 0;
List<int> rates = [];
List<List<String>> adj = [];
int nValves = 0;
List<int> node2valve = [];

int calc(int time, int mask, int pos) {
  if (time == 0) {
    return 0;
  }
  int res = dp[time][mask][pos];
  if (res >= 0) {
    return res;
  }
  res = 0;
  if (node2valve[pos] != -1 && ((mask >> node2valve[pos]) & 1) == 0) {
    int mask2 = mask | (1 << node2valve[pos]);
    res = max(res, calc(time - 1, mask2, pos) + (time - 1) * rates[pos]);
  }
  for (String node in adj[pos]) {
    res = max(res, calc(time - 1, mask, id[node]!));
  }
  return dp[time][mask][pos] = res;
}

void main(List<String> arguments) {
  File file = File('input.txt');

  for (String line in file.readAsLinesSync()) {
    List<String> tokens = line.split(' ');
    String node = tokens[1];
    nNodes++;
    id[node] = nNodes - 1;

    int rate = int.parse(numExp.firstMatch(tokens[4])!.group(0)!);
    rates.add(rate);

    if (rate > 0) {
      nValves++;
      node2valve.add(nValves - 1);
    } else {
      node2valve.add(-1);
    }

    adj.add([]);
    for (int i = 9; i < tokens.length; ++i) {
      adj.last.add(tokens[i].replaceAll(',', ''));
    }
  }

  dp = List.generate(
      31, (_) => List.generate(1 << nValves, (_) => List.filled(nNodes, -1)));
  // part 1
  print(calc(30, 0, id['AA']!));

  // part 2
  int res = 0;
  for (int manMask = 0; manMask < (1 << nValves); ++manMask) {
    int elephantMask = ((1 << nValves) - 1) ^ manMask;
    res = max(
        res, calc(26, manMask, id['AA']!) + calc(26, elephantMask, id['AA']!));
  }
  print(res);
}
