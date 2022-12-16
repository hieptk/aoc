import 'dart:io';
import 'dart:math';

final RegExp numExp = RegExp(r'-?[0-9]+');
final int inf = 1000000000;

late List<List<List<List<int>>>> dp;
Map<String, int> id = {};
List<String> name = [];
int nNodes = 0;
List<int> rates = [];
List<List<String>> adj = [];
int nValves = 0;
List<int> valve2node = [];
List<int> node2valve = [];

int calc(int time, int mask, int pos, int pos2) {
  if (time == 0) {
    return 0;
  }
  int res = dp[time][mask][pos][pos2];
  if (res >= 0) {
    return res;
  }
  res = 0;
  if (node2valve[pos] != -1 && ((mask >> node2valve[pos]) & 1) == 0) {
    int mask2 = mask | (1 << node2valve[pos]);
    if (node2valve[pos2] != -1 && ((mask2 >> node2valve[pos2]) & 1) == 0) {
      int mask3 = mask2 | (1 << node2valve[pos2]);
      res = max(res, calc(time - 1, mask3, pos, pos2) + (time - 1) * (rates[pos] + rates[pos2]));
    }
    for (String node in adj[pos2]) {
      res = max(res, calc(time - 1, mask2, pos, id[node]!) + (time - 1) * rates[pos]);
    }
  }
  if (node2valve[pos2] != -1 && ((mask >> node2valve[pos2]) & 1) == 0) {
    int mask2 = mask | (1 << node2valve[pos2]);
    for (String node in adj[pos]) {
      res = max(res, calc(time - 1, mask2, id[node]!, pos2) + (time - 1) * rates[pos2]);
    }
  }
  for (String node in adj[pos]) {
    for (String node2 in adj[pos2]) {
      res = max(res, calc(time - 1, mask, id[node]!, id[node2]!));
    }
  }
  return dp[time][mask][pos][pos2] = res;
}

void main(List<String> arguments) {
  File file = File('input.txt');

  for (String line in file.readAsLinesSync()) {
    List<String> tokens = line.split(' ');
    String node = line.split(' ')[1];
    nNodes++;
    id[node] = nNodes - 1;
    name.add(node);

    int rate = int.parse(numExp.firstMatch(tokens[4])!.group(0)!);
    rates.add(rate);

    if (rate > 0) {
      nValves++;
      node2valve.add(nValves - 1);
      valve2node.add(nNodes - 1);
    } else {
      node2valve.add(-1);
    }

    adj.add([]);
    for (int i = 9; i < tokens.length; ++i) {
      adj.last.add(tokens[i].replaceAll(',', ''));
    }
  }

  dp = List.generate(31, (_) => List.generate(1 << nValves, (_) => List.generate(nNodes, (_) => List.filled(nNodes, -1))));
  print(calc(26, 0, id['AA']!, id['AA']!));
}
