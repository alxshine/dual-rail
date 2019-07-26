from boundaries import *
from load import *

plt.figure()
plt.scatter(indices, pt, s=0.3)
plt.scatter(indices[diff!=0], pt[diff!=0], s=0.3, label='Points with nonzero HW difference')
plt.legend()
plt.show()

plt.figure()
indices = indices[diff!=0]
pt = pt[diff!=0]

plt.scatter(indices, pt, s=0.3)

unbalances = np.loadtxt('unbalances.csv').astype(np.int).flatten()
unbalances = np.unique(unbalances)
plt.scatter(indices[np.isin(pt, unbalances)], pt[np.isin(pt,unbalances)],s=0.4)

ldrb = np.loadtxt('ldrb.csv').flatten()
ldrb = np.unique(ldrb)
plt.scatter(indices[np.isin(pt, ldrb)], pt[np.isin(pt,ldrb)], s=0.4)

lsr = np.loadtxt('lsr.csv').flatten()
lsr = np.unique(lsr)
plt.scatter(indices[np.isin(pt,lsr)], pt[np.isin(pt,lsr)], s=0.4)

plt.legend()
plt.show()
