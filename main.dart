import 'dart:io';
import 'dart:math';

final RegExp numExp = RegExp(r'-?[0-9]+');
final inf = 4000000;

List<Point<int>> sensors = [];
List<Point<int>> beacons = [];

int checkRow(int y) {
  List<Point<int>> badRanges = [];
  for (int i = 0; i < sensors.length; ++i) {
    if (beacons[i].y == y && beacons[i].x >= 0 && beacons[i].x <= inf) {
      badRanges.add(Point(beacons[i].x, beacons[i].x));
    }
    int dx = (beacons[i].x - sensors[i].x).abs();
    int dy = (beacons[i].y - sensors[i].y).abs();
    int dist = dx + dy;
    // |x - xs| + |y - ys| <= dist
    if (dist >= (y - sensors[i].y).abs()) {
      int rx = min(dist - (y - sensors[i].y).abs() + sensors[i].x, inf);
      int lx = max(sensors[i].x - dist + (y - sensors[i].y).abs(), 0);
      if (lx <= rx) {
        badRanges.add(Point(lx, rx));
      }
    }
  }

  badRanges.sort((a, b) => a.x.compareTo(b.x));

  int maxx = -1, i = -1;
  while (i + 1 < badRanges.length && badRanges[i + 1].x <= maxx + 1) {
    i++;
    maxx = max(maxx, badRanges[i].y);
  }

  return maxx + 1;
}

void main(List<String> arguments) {
  File file = File('input.txt');

  for (String line in file.readAsLinesSync()) {
    List<int> nums = numExp.allMatches(line).map((e) => int.parse(e.group(0)!)).toList();
    sensors.add(Point(nums[0], nums[1]));
    beacons.add(Point(nums[2], nums[3]));
  }

  for (int y = 0; y <= inf; ++y) {
    int x = checkRow(y);
    if (x >= 0 && x <= inf) {
      print(x * inf + y);
      exit(0);
    }
  }
}
