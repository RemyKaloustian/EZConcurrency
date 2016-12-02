


import matplotlib.pyplot as plt
import sys

f = open(sys.argv[1], "r")
dico = dict()
dico['0'] = []
dico['1'] = []
dico['2'] = []
absisse = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512]

for line in f:
    line = line.rstrip("\n")
    line = line.replace(",", ".")
    line = line.replace("  ", " ")
    data = line.split(" ")
    print(data  )
    l = []
    for a in data:
        if (len(a) > 0 and a != " " and a != "Over"):
            l = l +  [a]
    if (len(l) > 1):
        dico[data[0]] = dico[data[0]] + [l[2:]]
tpCPU0 = []
tpUSER0 = []

tpCPU1 = []
tpUSER1 = []

tpCPU2 = []
tpUSER2 = []
for v in dico['0']:
    tpCPU0 =tpCPU0+ [float(v[0])]
    tpUSER0 = tpUSER0+ [float(v[1])]
for v in dico['1']:
    tpCPU1 =tpCPU1+[float(v[0])]
    tpUSER1 = tpUSER1+ [float(v[1])]

for v in dico['2']:
    tpCPU2 =tpCPU2+ [float(v[0])]
    tpUSER2 = tpUSER2+ [float(v[1])]

plt.xlabel('nombre personne')
plt.ylabel('temps (ms)')
plt.yscale('log')
#plt.xscale('log')


plt.plot(absisse,tpCPU0, label="USER_0", color="blue")
plt.plot(absisse,tpUSER0, label="CPU_0", color="red" )

plt.plot(absisse,tpCPU1, label="version_1", color="gold" )
plt.plot(absisse,tpUSER1, label="version_1", color="green" )
#
plt.plot(absisse,tpCPU2, label="version_2", color="black" )
plt.plot(absisse,tpUSER2, label="version_2", color="purple" )



plt.show()
