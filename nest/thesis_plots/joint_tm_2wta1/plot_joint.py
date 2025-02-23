import numpy as np
import shared_params
import pickle
from matplotlib import pyplot as plt
from sklearn.metrics import mean_squared_error

np.random.seed(1)


with open('nest_data.pkl', 'rb') as f:
    data_nest = pickle.load(f)
with open('klampfl_data.pkl', 'rb') as f:
    data_klampfl = pickle.load(f, encoding='latin1')

fig, axes = plt.subplots(5, 1, sharex=True)
fig.set_figwidth(9)
fig.set_figheight(12)

c_nest = 'tomato'
c_klampfl = 'cornflowerblue'
c_both = 'black'
ls = ['-', '--']
lw1 = 2.5
neuron_ids = {'nest': [1, 2], 'klampfl': [0, 1]}
input_ids = {'nest': [8], 'klampfl': [0, 1]}

# for idx, key in enumerate(['inp_spikes', 'spikes', 'Vms', 'epsps', 'inp_weights', 'rec_weights',  ][:4]):
#     axes[idx].plot

# Input spikes
for idx, n in enumerate(neuron_ids['klampfl']):
    if idx == 0:
        indices = np.where(data_klampfl['inp_spikes'][n][1])[0]
        times = data_klampfl['inp_spikes'][n][0][indices]
        axes[0].plot(times, [idx] * len(times), 'o', color=c_both)

# Output spikes
for idx, n in enumerate(neuron_ids['nest']):
    times = data_nest['spikes'][n]
    axes[1].plot(times, [idx] * len(times), 'v', ms=12, color=c_nest, alpha=0.9, label="NEST" if idx==0 else "")
for idx, n in enumerate(neuron_ids['klampfl']):
    indices = np.where(data_klampfl['spikes'][n][1])[0]
    times = data_klampfl['spikes'][n][0][indices]
    axes[1].plot(times, [idx] * len(times), 'o', ms=12, color=c_klampfl, alpha=0.5, label="Klampfl" if idx==0 else "")
axes[1].legend()

# Vms
for idx, (n, n2) in enumerate(zip(neuron_ids['nest'], neuron_ids['klampfl'])):
    axes[2].plot(data_nest['Vms'][n][0], data_nest['Vms'][n][1], color=c_nest, ls=ls[0], lw=lw1, label="NEST" if idx==1 else "")  #  marker='o',
    axes[2].plot(data_klampfl['Vms'][n2][0], data_klampfl['Vms'][n2][1], color=c_klampfl, ls=ls[1], lw=lw1, label="Klampfl" if idx==1 else "")  # marker='o',
    # print(f"Vm diff: {mean_squared_error(data_nest['Vms'][n][1], data_klampfl['Vms'][n2][1][:-1])}")
axes[2].legend()

# Input weights
for neuron_idx, (n, n2) in enumerate(zip(neuron_ids['nest'], neuron_ids['klampfl'])):
    for idx, (n_i, n_i2) in enumerate(zip(input_ids['nest'], input_ids['klampfl'])):
        axes[3].plot(data_nest['inp_weights'][n][n_i][0], data_nest['inp_weights'][n][n_i][1],
                     color=c_nest, ls=ls[idx], lw=lw1, label="NEST" if neuron_idx==0 else "")  # marker='o'

    kw = data_klampfl['inp_weights'][1][:, neuron_idx, 0]
    axes[3].plot(data_klampfl['inp_weights'][0], kw, color=c_klampfl, ls=ls[1], lw=lw1, label="Klampfl" if neuron_idx==0 else "") # marker='o',
axes[3].legend()

# Recurrent weights
# for neuron_idx, (n, n2) in enumerate(zip(neuron_ids['nest'], neuron_ids['klampfl'])):
for k, v in data_nest['rec_weights'].items():
    for k2, v2 in v.items():
        if len(v2[0]) > 1:
            axes[4].plot(v2[0], v2[1], color=c_nest, ls=ls[0], lw=lw1, label="NEST" if k==1 else "")

for idx, n in enumerate(neuron_ids['klampfl']):
    for idx2, n2 in enumerate(neuron_ids['klampfl']):
        if n != n2:
            axes[4].plot(data_klampfl['rec_weights'][0], data_klampfl['rec_weights'][1][:, n, n2],
                         color=c_klampfl, ls=ls[1], lw=lw1, label="Klampfl" if idx==0 else "")
axes[4].legend()

# kw = data_klampfl['inp_weights'][1][:, neuron_idx, 0]
    # print(f"Vm diff: {mean_squared_error(data_nest['Vms'][n][1], data_klampfl['Vms'][n2][1][:-1])}")

axes[0].set_title('Input spikes')
axes[1].set_title('Output spikes')
axes[2].set_title('Voltage trace')
# axes[2].set_ylim([-0.2, 0.1])

axes[3].set_title('Input weights')
axes[4].set_title('Recurrent weights')

plt.xlim(shared_params.xlim)
plt.tight_layout()
plt.show()