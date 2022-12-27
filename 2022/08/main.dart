import 'dart:io';
import 'dart:math';

int m = 0, n = 0;
late List<List<int>> h;

void main(List<String> arguments) {
  File file = File('input.txt');
  List<String> a = file.readAsLinesSync();
  m = a.length;
  n = a[0].length;
  h = List.generate(m, (i) => List.generate(n, (j) => a[i].codeUnitAt(j) - 48));

  List<List<int>> ok = List.generate(m, (_) => List.filled(n, 0));
  List<List<int>> score = List.generate(m, (_) => List.filled(n, 1));

  List<int> st = List.empty(growable: true);
  for (int i = 0; i < m; ++i) {
    st.clear();
    for (int j = 0; j < n; ++j) {
      while (st.length > 0 && h[i][j] > h[i][st.last]) {
        st.removeLast();
      }
      if (st.length > 0) {
        score[i][j] *= j - st.last;
      } else {
        ok[i][j] = 1;
        score[i][j] *= j;
      }
      st.add(j);
    }
    st.clear();
    for (int j = n - 1; j >= 0; --j) {
      while (st.length > 0 && h[i][j] > h[i][st.last]) {
        st.removeLast();
      }
      if (st.length > 0) {
        score[i][j] *= st.last - j;
      } else {
        ok[i][j] = 1;
        score[i][j] *= n - 1 - j;
      }
      st.add(j);
    }
  }

  for (int j = 0; j < n; ++j) {
    st.clear();
    for (int i = 0; i < m; ++i) {
      while (st.length > 0 && h[i][j] > h[st.last][j]) {
        st.removeLast();
      }
      if (st.length > 0) {
        score[i][j] *= i - st.last;
      } else {
        ok[i][j] = 1;
        score[i][j] *= i;
      }
      st.add(i);
    }
    st.clear();
    for (int i = m - 1; i >= 0; --i) {
      while (st.length > 0 && h[i][j] > h[st.last][j]) {
        st.removeLast();
      }
      if (st.length > 0) {
        score[i][j] *= st.last - i;
      } else {
        ok[i][j] = 1;
        score[i][j] *= m - 1 - i;
      }
      st.add(i);
    }
  }

  print(ok.fold<int>(0, (res, row) => res + row.reduce((a, b) => a + b)));
  print(score.fold<int>(0, (res, row) => max(res, row.reduce(max))));
}
