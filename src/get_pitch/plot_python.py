# Load the required libraries:
#   * scipy
#   * numpy
#   * matplotlib
<<<<<<< HEAD
#from scipy.io import wavfile
=======
from scipy.io import wavfile
>>>>>>> 360aeff848ebe4c182e35d9e98b2b0085fb42593
#from scipy.signal import find_peaks
from matplotlib import pyplot as plt
#import numpy as np
#from pydub import AudioSegment
#import librosa
<<<<<<< HEAD
#import statsmodels.api as sm
import sndfile as sf
=======
import statsmodels.api as sm
#import soundfile as sf
>>>>>>> 360aeff848ebe4c182e35d9e98b2b0085fb42593

#cut the signal
t1 = 0 * 1000 #Works in milliseconds
t2 = 370 * 1000
newAudio = AudioSegment.from_wav("rl002.wav")
newAudio = newAudio[t1:t2]
newAudio.export('rl002_fragment.wav', format="wav") #Exports to a wav file in the current path.

#senyal_original, f = sf.read('rl002.wav ')

# Load data and sampling frequency from the data file
#D = int(0.03 * f)
#r = np.zeros(D)
#T0 = int(0.621 * f)
samplerate, data = wavfile.read('rl002_fragment.wav')
#senyal = senyal_original[T0:T0+D]

# Get some useful statistics
T = 1/samplerate # Sampling period
N = len(data) # Signal length in samples
t = N / samplerate # Signal length in seconds


#Y_k = np.fft.fft(data)[0:int(N/2)]/N # FFT
#Y_k[1:] = 2*Y_k[1:] # Single-sided spectrum
#Pxx = np.abs(Y_k) # Power spectrum

#f = samplerate * np.arange((N/2)) / N; # frequencies
auto = sm.tsa.acf(data, nlags=600)

#for k in range(D):
 #   for n in range(len(senyal)-k):
  #      r[k] = r[k] + (senyal[n]* senyal[k+n])   
   # r[k] = r[k] /len(senyal)

# plotting
fig,ax = plt.subplots()
plt.plot(auto)
#plt.plot(f[0:5000], Pxx[0:5000], linewidth=2)
plt.ylabel('Amplitude')
plt.xlabel('Frequency [Hz]')
plt.show()



#######################################

# Load the data and calculate the time of each sample
#samplerate, data = wavfile.read('rl002.wav')
#times = np.arange(len(data))/float(samplerate)

# Make the plot
# You can tweak the figsize (width, height) in inches
#plt.figure(figsize=(30, 4))
#plt.fill_between(times, data)
#plt.xlim([0.340,0.370])
#plt.xlabel('time (s)')
#plt.ylabel('amplitude')
# You can set the format by changing the extension
# like .pdf, .svg, .eps
#plt.savefig('plot.png', dpi=100)
#plt.show()