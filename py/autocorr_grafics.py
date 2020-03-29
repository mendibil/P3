import matplotlib.pyplot as plt
import numpy as np
import wave
import sys

spf = wave.open("py/vocal_o.wav", "r")

signal = spf.readframes(-1)
signal = np.frombuffer(signal, "Int16")
trunc = round(len(signal)/2)+15
llarg = 1000
signal = signal[trunc : trunc + llarg]
signal = signal/max(signal)

# Autocorrelation
r = [0] * llarg
for k in range(0, len(r)):
        for m in range(0, len(signal)-k-1):
                r[k] += signal[m]*signal[m+k]
        r[k] = r[k] / len(signal)

fs = 16e3
Time = np.linspace(0, len(signal) / fs, num=len(signal))

fig, axs = plt.subplots(2)
plt.subplots_adjust(wspace=1, hspace=0.6)
fig.suptitle("Vocal /o/")
axs[0].plot(Time,signal)
axs[0].title.set_text('Señal temporal')
axs[0].set_xlabel('Time [s]')
axs[0].grid(linestyle='dotted')
axs[0].margins(0)
axs[0].set_ylim([min(signal)-0.08, max(signal)+0.08])
# plt[0].ylim(min(signal)-0.2, max(signal)+0.2)
axs[1].plot(r)
axs[1].title.set_text('Autocorrelación')
axs[1].margins(0)
axs[1].grid(linestyle='dotted')
axs[1].set_ylim([min(r)-0.08, max(r)+0.03])
plt.show()

spf.close()