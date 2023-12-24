from z3 import *

def main():
    stones = []
    with open('input2.txt') as f:
        for line in f.readlines()[:3]:
            stones.append((int(token) for token in line.split()))
    x0, y0, z0, vx0, vy0, vz0 = Reals('x0 y0 z0 vx0 vy0 vz0')
    t = [Real(f't{i}') for i in range(3)]
    s = Solver()
    for (x, y, z, vx, vy, vz), t in zip(stones, t):
        s.add(x + vx * t == x0 + vx0 * t)
        s.add(y + vy * t == y0 + vy0 * t)
        s.add(z + vz * t == z0 + vz0 * t)
    s.check()
    m = s.model()
    print(m[x0].as_long() + m[y0].as_long() + m[z0].as_long())


if __name__ == "__main__":
    main()