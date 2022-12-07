import 'dart:io';
import 'dart:math';

const int FS_SIZE = 70000000;
const int REQUIRED_SIZE = 30000000;

int res = 0;
int res2 = 0;

class Node {
  int size = 0;
  Map<String, Node> children = {};
  Node? parent = null;
  late int totalSize = children.values.fold<int>(size, (int sum, Node child) => sum + child.totalSize);
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

void part1(Node p) {
  p.children.values.forEach((child) => part1(child));
  if (p.totalSize <= 100000) {
    res += p.totalSize;
  }
}

void part2(Node p, int minSize) {
  res2 = min(res2, p.totalSize);
  p.children.values.forEach((child) {
    if (child.totalSize >= minSize) {
      part2(child, minSize);
    }
  });
}

void main(List<String> arguments) {
  File file = File('input.txt');
  Node root = Node();
  Node cur = root;
  for (String line in file.readAsLinesSync()) {
    List<String> tokens = line.split(' ');
    if (tokens[0] == '\$' && tokens[1] == 'cd') {
      if (tokens[2] == '..') {
        cur = cur.parent!;
      } else if (tokens[2] == '/') {
        cur = root;
      } else {
        addChild(cur, tokens[2]);
        cur = cur.children[tokens[2]]!;
      }
    } else if (tokens[0] != '\$' && tokens[0] != 'dir') {
      cur.size += int.parse(tokens[0]);
    }
  }

  part1(root);
  print(res);

  res2 = root.totalSize;
  part2(root, REQUIRED_SIZE - (FS_SIZE - root.totalSize));
  print(res2);
}