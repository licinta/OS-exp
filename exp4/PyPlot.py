import matplotlib.pyplot as plt
from matplotlib import animation
import numpy as np
import sys

# 读取管道输入
data = sys.stdin.readlines()

# 解析数据
x = []
y1 = []
y2 = []
y3 = []
y4 = []
y5 = []
for line in data:
    parts = line.strip('\n').split('\t')
    x.append(int(parts[0][:2]))
    y1.append(float(parts[1][len("FIFO") + 1:]))
    y2.append(float(parts[2][len("LRU") + 1:]))
    y3.append(float(parts[3][len("LFU") + 1:]))
    y4.append(float(parts[4][len("OPT") + 1:]))
    y5.append(float(parts[5][len("CLOCK") + 1:]))

# 绘制动态折线图

fig, ax = plt.subplots()
fig.set_size_inches(8, 6)
ax.set_xlim(4, 32)
ax.set_ylim(0.4, 1)
ax.set_xlabel("Page Frames' Number")
ax.set_ylabel('Hit Ratio')
line1, = ax.plot([], [], label='FIFO')
line2, = ax.plot([], [], label='LRU')
line3, = ax.plot([], [], label='OPT')
line4, = ax.plot([], [], label='LFU')
line5, = ax.plot([], [], label='CLOCK')
lines = [line1, line2, line3, line4, line5]
ax.legend()


def update(i):
    for j in range(5):
        lines[j].set_data(x[:i], [y1[:i], y2[:i], y3[:i], y4[:i], y5[:i]][j])
    return lines


ani = animation.FuncAnimation(fig, update, frames=144, interval=100, blit=True)
ani.save("End.gif", writer="ffmpeg", dpi=100, fps=144)

plt.show()
