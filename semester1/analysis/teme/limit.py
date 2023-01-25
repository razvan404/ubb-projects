import matplotlib.pyplot as plt
import math
x = []
y = []

n = input()
n = int(n)
lim = 0
k = 1
for i in range(1, n + 1):
    x.append(i)
    k = k * i
    lim += math.sin(k)/(i * (i + 1))
    y.append(lim)
print(lim)
plt.plot(x, y)

plt.xlabel('axa oX')
plt.ylabel('axa oY')

plt.title('limită analiză')

plt.show()