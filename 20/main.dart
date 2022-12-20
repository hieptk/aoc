import 'dart:io';

final bool part1 = false;
final int N_MIX = part1 ? 1 : 10;

void main(List<String> arguments) {
  File file = File('input.txt');
  List<int> nums = file.readAsLinesSync().map((e) => int.parse(e)).toList();
  if (!part1) {
    nums = nums.map((e) => e * 811589153).toList();
  }
  int n = nums.length;
  List<int> pos = List.generate(n, (index) => index);
  List<int> idx = List.generate(n, (index) => index);
  for (int mix = 0; mix < N_MIX; ++mix) {
    for (int i = 0; i < n; ++i) {
      int j = pos[i];
      int k = (nums[j] % (n - 1) + (n - 1)) % (n - 1);
      for (int u = 0; u < k; ++u) {
        int j2 = (j + 1) % n;
        int tmp = nums[j];
        nums[j] = nums[j2];
        nums[j2] = tmp;
        int i2 = idx[j2];
        idx[j] = i2;
        idx[j2] = i;
        pos[i] = j2;
        pos[i2] = j;
        j = j2;
      }
    }
  }
  int p0 = nums.indexOf(0);
  print(nums[(p0 + 1000) % n] + nums[(p0 + 2000) % n] + nums[(p0 + 3000) % n]);
}
