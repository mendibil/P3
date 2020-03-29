import matplotlib.pyplot as plt
import numpy as np

file = open("rl004.f0", 'r')
median = []
for line in file.readlines():
    median.append(float(line))
file.close()

file = open("rl004_no_mediana.f0", 'r')
no_median = []
for line in file.readlines():
    no_median.append(float(line))
file.close()

plt.plot(median,   'bo', markersize = 4, label='Con filtro de mediana')
plt.plot(no_median, 'ro', markersize = 2, label='Sin filtro de mediana')
plt.title('Comparación filtro de mediana')
plt.grid(linestyle='dotted')
plt.legend(loc=0, bbox_to_anchor=(0.6,0.6))
plt.show()