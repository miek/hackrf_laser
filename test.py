import numpy as np
import matplotlib.pyplot as plt
import sys

plt.axis([-2047, 2047, -2047, 2047])
plt.ion()

for line in sys.stdin:
    print line
    coord_list = map(int, line.strip().strip(',').split(','))
    coord_iter = iter(coord_list)
    coords = zip(coord_iter, coord_iter)
    x, y = zip(*coords)
    fig, ax = plt.subplots()
    ax.clear()
    ax.scatter(x, y)
    plt.pause(0.05)
