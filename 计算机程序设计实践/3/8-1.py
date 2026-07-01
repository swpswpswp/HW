import numpy as np
import matplotlib.pyplot as plt

x = np.arange(-2*np.pi, 2*np.pi, 0.01)

y1 = np.sin(2*x)/x
y2 = np.sin(3*x)/x

plt.figure(figsize=(8, 6))
plt.plot(x, y1, 'k--', label='sin2x/x')
plt.plot(x, y2, 'r-.', label='sin3x/x')

# 设置坐标轴范围
plt.xlim(-2*np.pi-0.5, 2*np.pi+0.5)
plt.ylim(-1, 4)

# 设置x轴的刻度值
plt.xticks([-2*np.pi, -np.pi, 0, np.pi, 2*np.pi],
           ['-2π', '-π', '0', 'π', '2π'])

# 设置x轴label
plt.xlabel('弧度', fontproperties='FangSong', fontsize=14)
plt.ylabel('正弦', fontproperties='FangSong', fontsize=14)
plt.title('线形图', fontproperties='FangSong', fontsize=14)

plt.legend()  # 添加图例
plt.grid(linestyle='--')  # 添加网格线
plt.savefig('figures/exercise8-1.jpg')  # 保存图形文件
plt.show()
