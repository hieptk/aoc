import 'dart:io';

Map<String, List<String>> adj = {};
Map<String, List<String>> adjRev = {};
Map<String, String> op = {};
Map<String, int> val = {};

num calc(String id) {
  if (val.containsKey(id)) {
    return val[id]!;
  }
  List<num> adjVals = adj[id]!.map((e) => calc(e)).toList();
  String o = op[id]!;
  if (o == '+') {
    return adjVals[0] + adjVals[1];
  } else if (o == '-') {
    return adjVals[0] - adjVals[1];
  } else if (o == '*') {
    return adjVals[0] * adjVals[1];
  } else if (o == '/') {
    return adjVals[0] / adjVals[1];
  } else {
    return adjVals[0];
  }
}

void reverseOp(String id, String pid) {
  if (adj.containsKey(id)) {
    String o = op[id]!;
    int idx = adj[id]!.indexOf(pid);
    String other = adj[id]![1 - idx];
    if (o == '+') {
      adj[pid] = [id, other];
      op[pid] = '-';
    } else if (o == '-') {
      if (idx == 0) {
        adj[pid] = [id, other];
        op[pid] = '+';
      } else {
        adj[pid] = [other, id];
        op[pid] = '-';
      }
    } else if (o == '*') {
      adj[pid] = [id, other];
      op[pid] = '/';
    } else if (o == '/') {
      if (idx == 0) {
        adj[pid] = [id, other];
        op[pid] = '*';
      } else {
        adj[pid] = [other, id];
        op[pid] = '/';
      }
    } else {
      adj[pid] = [other];
      op[pid] = '=';
    }
  }
  if (!adjRev.containsKey(id)) {
    return;
  }
  assert(adjRev[id]!.length == 1);
  reverseOp(adjRev[id]![0], id);
}

void addRev(String u, String  v) {
  adjRev.putIfAbsent(u, () => []);
  adjRev[u]!.add(v);
}

void main(List<String> arguments) {
  File file = File('input.txt');
  for (String line in file.readAsLinesSync()) {
    List<String> tokens = line.split(' ');
    String id = tokens[0].substring(0, tokens[0].length - 1);
    if (tokens.length == 2) {
      val[id] = int.parse(tokens[1]);
    } else {
      adj[id] = [tokens[1], tokens[3]];
      op[id] = tokens[2];
      addRev(tokens[1], id);
      addRev(tokens[3], id);
    }
  }

  print(calc('root'));

  op['root'] = '=';
  reverseOp('humn', '');
  val.remove('humn');
  print(calc('humn'));
}
