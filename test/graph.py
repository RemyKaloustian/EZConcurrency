import matplotlib.pyplot as plt

f1 = open("with_thread.txt", "r")

x1 = []
y1 = []

x2 = []
y2 = []

for line in f1:
    x1 = x1 + [float(line.split()[1])]
    y1 = y1 + [[float(line.split()[0])]]
print (x1)
print (y1)
x1.sort()
y1.sort()
f1 = open("without_thread.txt", "r")
for line in f1:
    x2 = x2 + [float(line.split()[1])]
    y2 = y2 + [[float(line.split()[0])]]
x2.sort()
y2.sort()

plt.grid(True)
plt.plot(x1,y1, "b", linewidth=0.8, marker="*", label="threading")
plt.plot(x2, y2, "g", linewidth=0.8, marker="+", label="no threading")
plt.xlabel('Vitesse')
plt.ylabel('Temps')
plt.legend()
plt.show()

plt.show()
