#!/usr/bin/python2

import numpy as np
import sys
import matplotlib.pyplot as plt

p_balanced = "balanced.npy"
p_unbalanced = "unbalanced.npy"
start_index = 1000
end_index = 1400

try:
    index = int(sys.arv[1])
except Exception:
    index = 0

balanced = np.load(p_balanced)
unbalanced = np.load(p_unbalanced)

evens = balanced[::2, start_index:end_index]
odds = balanced[1::2, start_index:end_index]

evens_un = unbalanced[::2, start_index:end_index]
odds_un = unbalanced[1::2, start_index:end_index]

evens_mean = evens.mean(axis=0)
odds_mean = odds.mean(axis=0)
diff = evens_mean - odds_mean

eu_mean = evens_un.mean(axis=0)
ou_mean = odds_un.mean(axis=0)
diff_un = eu_mean - ou_mean

print("balanced: {}, unbalanced: {}".format(diff[211], diff_un[211]))

ymax = max(max(diff), max(diff_un))
ymin = min(min(diff), min(diff_un))

plt.figure()
plt.subplot(311)
plt.title("balanced")
plt.ylim(ymin, ymax)
plt.plot(diff)

plt.subplot(312)
plt.title("unbalanced")
plt.ylim(ymin, ymax)
plt.plot(diff_un)

plt.subplot(313)
plt.title("both")
plt.plot((diff), label="balanced")
plt.plot((diff_un), label="unbalanced")
plt.ylim(ymin, ymax)
plt.legend()

plt.show()
