from z3 import *

class Stone:
    def __init__(self, x, y, z, vx, vy, vz):
        self.x = x
        self.y = y
        self.z = z
        self.vx = vx
        self.vy = vy
        self.vz = vz

def main():
    with open('input.txt') as f:
        lines = f.readlines()[:3]
    stones = []
    for line in lines:
        tokens = line.split(' ')
        stones.append(Stone(int(tokens[0]), int(tokens[1]), int(tokens[2]), int(tokens[3]), int(tokens[4]), int(tokens[5])))
    x0, y0, z0, vx, vy, vz = Reals('x0 y0 z0 vx vy vz')
    t = [Real(f't{i}') for i in range(3)]
    s = Solver()
    for i in range(3):
        s.add(stones[i].x + stones[i].vx * t[i] == x0 + vx * t[i])
        s.add(stones[i].y + stones[i].vy * t[i] == y0 + vy * t[i])
        s.add(stones[i].z + stones[i].vz * t[i] == z0 + vz * t[i])
    s.check()
    m = s.model()
    print(m[x0].as_long() + m[y0].as_long() + m[z0].as_long())


if __name__ == "__main__":
    main()