import matplotlib.pyplot as plt
import numpy as np
import serial
import time

serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)
k = s.readline()

Fs = int(float(k));  # sampling rate
Ts = 1.0/Fs; # sampling interval
t = np.arange(0,100*Ts,Ts) # time vector; create Fs samples between 0 and 1.0 sec.
y = np.arange(0,100*Ts,Ts) # signal vector; create Fs samples

n = len(y) # length of the signal
print(n)
k = np.arange(n)
T = n/Fs
frq = k/T # a vector of frequencies; two sides frequency range
frq = frq[range(int(n/2))] # one side frequency ranges

for x in range(0, n):
    line=s.readline() # Read an echo string from B_L4S5I_IOT01A terminated with '\n'
    print(line)
    y[x] = float(line)

Y = np.fft.fft(y)/n*2 # fft computing and normalization
Y = Y[range(int(n/2))] # remove the conjugate frequency parts

fig, ax = plt.subplots(2, 1)
ax[0].plot(t,y)
ax[0].set_xlabel('Time')
ax[0].set_ylabel('Amplitude')
ax[1].plot(frq,abs(Y),'r') # plotting the spectrum
ax[1].set_xlabel('Freq (Hz)')
ax[1].set_ylabel('|Y(freq)|')
plt.show()
s.close()