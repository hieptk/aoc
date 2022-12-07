import 'dart:io';
import 'dart:math';

int res = 0;
int res2 = 0;
int fsSize = 70000000;
int requiredSize = 30000000;

class Node {
  int size = 0, totalSize = 0;
  Map<String, Node> children = {};
  Node? parent = null;
}

void addChild(Node p, String childName, {int size: 0}) {
  if (p.children.containsKey(childName)) {
    return;
  }
  Node child = Node();
  child.parent = p;
  child.size = size;
  p.children[childName] = child;
}

void calcTotalSize(Node p) {
  p.totalSize = p.size;
  for (String child in p.children.keys) {
    calcTotalSize(p.children[child]!);
    p.totalSize += p.children[child]!.totalSize;
  }
  if (p.size == 0 && p.totalSize <= 100000) {
    res += p.totalSize;
  }
}

void findToDelete(Node p, int minSize) {
  res2 = min(res2, p.totalSize);
  for (String child in p.children.keys) {
    if (p.children[child]!.totalSize >= minSize) {
      findToDelete(p.children[child]!, minSize);
    }
  }
}

void main(List<String> arguments) {
  File file = File('input.txt');
  List<String> lines = file.readAsLinesSync();
  Node root = Node();
  Node cur = root;
  for (int i = 0; i < lines.length; ++i) {
    List<String> tokens = lines[i].split(' ');
    if (tokens[1] == 'cd') {
      if (tokens[2] == '..') {
        if (cur.parent != null) {
          cur = cur.parent!;
        }
      } else if (tokens[2] == '/') {
        cur = root;
      } else {
        addChild(cur, tokens[2]);
        cur = cur.children[tokens[2]]!;
      }
    } else {
      int j = i;
      while (j + 1 < lines.length && !lines[j + 1].startsWith('\$')) {
        j++;
        List<String> tokens = lines[j].split(' ');
        if (tokens[0] == 'dir') {
          addChild(cur, tokens[1]);
        } else {
          addChild(cur, tokens[1], size: int.parse(tokens[0]));
        }
      }
      j = i;
    }
  }

  calcTotalSize(root);
  print(res);

  res2 = root.totalSize;
  findToDelete(root, requiredSize - (fsSize - root.totalSize));
  print(res2);
}
