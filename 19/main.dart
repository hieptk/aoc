import 'dart:io';
import 'dart:math';

final bool part1 = false;
final int T = part1 ? 24 : 32;
final RegExp numExp = RegExp(r'[0-9]+');

class State {
  final int t;
  final int ore, clay, obs;
  final int oreRobot, clayRobot, obsRobot, geoRobot;

  State(this.t, this.ore, this.clay, this.obs, this.oreRobot, this.clayRobot,
      this.obsRobot, this.geoRobot);

  @override
  bool operator ==(Object other) =>
      other is State &&
      other.t == t &&
      other.ore == ore &&
      other.clay == clay &&
      other.obs == obs &&
      other.oreRobot == oreRobot &&
      other.clayRobot == clayRobot &&
      other.obsRobot == obsRobot &&
      other.geoRobot == geoRobot;

  int get hashCode =>
      Object.hash(t, ore, clay, obs, oreRobot, clayRobot, obsRobot, geoRobot);
}

late int oreCost, clayCost, obsOreCost, obsClayCost, geoOreCost, geoObsCost;
Map<State, int> dp = {};

int calc(State state) {
  if (state.t == 0) {
    return 0;
  }
  if (dp.containsKey(state)) {
    return dp[state]!;
  }
  int res = 0;
  if (state.ore >= geoOreCost && state.obs >= geoObsCost) {
    return dp[state] = state.geoRobot +
        calc(State(
            state.t - 1,
            state.ore + state.oreRobot - geoOreCost,
            state.clay + state.clayRobot,
            state.obs + state.obsRobot - geoObsCost,
            state.oreRobot,
            state.clayRobot,
            state.obsRobot,
            state.geoRobot + 1));
  }
  if (state.ore >= obsOreCost && state.clay >= obsClayCost) {
    return dp[state] = state.geoRobot +
        calc(State(
            state.t - 1,
            state.ore + state.oreRobot - obsOreCost,
            state.clay + state.clayRobot - obsClayCost,
            state.obs + state.obsRobot,
            state.oreRobot,
            state.clayRobot,
            state.obsRobot + 1,
            state.geoRobot));
  }
  if (state.ore >= clayCost) {
    res = state.geoRobot +
        calc(State(
            state.t - 1,
            state.ore + state.oreRobot - clayCost,
            state.clay + state.clayRobot,
            state.obs + state.obsRobot,
            state.oreRobot,
            state.clayRobot + 1,
            state.obsRobot,
            state.geoRobot));
  }
  if (state.ore >= oreCost) {
    res = max(
        res,
        state.geoRobot +
            calc(State(
                state.t - 1,
                state.ore + state.oreRobot - oreCost,
                state.clay + state.clayRobot,
                state.obs + state.obsRobot,
                state.oreRobot + 1,
                state.clayRobot,
                state.obsRobot,
                state.geoRobot)));
  }
  res = max(
      res,
      state.geoRobot +
          calc(State(
              state.t - 1,
              state.ore + state.oreRobot,
              state.clay + state.clayRobot,
              state.obs + state.obsRobot,
              state.oreRobot,
              state.clayRobot,
              state.obsRobot,
              state.geoRobot)));

  return dp[state] = res;
}

void main(List<String> arguments) {
  File file = File('input.txt');
  int res = 0;
  List<int> res2 = [];
  for (String line in file.readAsLinesSync()) {
    dp.clear();
    print(res2.length + 1);
    List<int> nums =
        numExp.allMatches(line).map((e) => int.parse(e.group(0)!)).toList();
    oreCost = nums[1];
    clayCost = nums[2];
    obsOreCost = nums[3];
    obsClayCost = nums[4];
    geoOreCost = nums[5];
    geoObsCost = nums[6];

    int tmp = calc(State(T, 0, 0, 0, 1, 0, 0, 0));
    print('Explored ${dp.length} states');
    res += nums[0] * tmp;

    res2.add(tmp);
    if (!part1 && res2.length == 3) {
      break;
    }
  }

  if (part1) {
    print(res);
  } else {
    print(res2[0] * res2[1] * res2[2]);
  }
}
