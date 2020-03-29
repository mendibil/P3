import matplotlib.pyplot as plt
import numpy as np

file = open("pitch_db/train/rl018.f0ref", 'r')
ref = []
for line in file.readlines():
    ref.append(float(line))
file.close()

file = open("pitch_db/train/rl018.f0", 'r')
estim = []
for line in file.readlines():
    estim.append(float(line))
file.close()

plt.plot(ref,   'bo', markersize = 3, label='Referencia')
plt.plot(estim, 'ro', markersize = 2, label='Estimado')
plt.title('Pitch de referencia y pitch estimado')
plt.grid(linestyle='dotted')
plt.legend()
plt.show()