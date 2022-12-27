import 'dart:io';
import 'dart:math';

const int FS_SIZE = 70000000;
const int REQUIRED_SIZE = 30000000;

int res = 0;
int res2 = 0;

class Directory {
  int size = 0;
  Map<String, Directory> children = {};
  Directory? parent = null;
  late int totalSize = children.values
      .fold<int>(size, (int sum, Directory child) => sum + child.totalSize);
}

void addChild(Directory p, String childName, List<Directory> allDirs) {
  if (p.children.containsKey(childName)) {
    return;
  }
  Directory child = Directory();
  child.parent = p;
  p.children[childName] = child;
  allDirs.add(child);
}

void main(List<String> arguments) {
  File file = File('input.txt');
  Directory root = Directory();
  Directory cur = root;
  List<Directory> allDirs = [root];
  for (String line in file.readAsLinesSync()) {
    List<String> tokens = line.split(' ');
    if (tokens[0] == '\$' && tokens[1] == 'cd') {
      if (tokens[2] == '..') {
        cur = cur.parent!;
      } else if (tokens[2] == '/') {
        cur = root;
      } else {
        addChild(cur, tokens[2], allDirs);
        cur = cur.children[tokens[2]]!;
      }
    } else if (tokens[0] != '\$' && tokens[0] != 'dir') {
      cur.size += int.parse(tokens[0]);
    }
  }

  print(allDirs
      .where((dir) => dir.totalSize <= 100000)
      .fold<int>(0, (sum, dir) => sum + dir.totalSize));

  int minSize = REQUIRED_SIZE - (FS_SIZE - root.totalSize);
  print(allDirs
      .where((dir) => dir.totalSize >= minSize)
      .fold<int>(root.totalSize, (res, dir) => min(res, dir.totalSize)));
}
