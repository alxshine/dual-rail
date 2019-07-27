from boundaries import *
from load import *

plt.figure()
plt.scatter(indices, pt, s=0.3)
plt.scatter(indices[diff!=0], pt[diff!=0], s=0.3, label='Points with nonzero HW difference')
plt.legend()
plt.xlabel('Time')
plt.ylabel('Line in assembly file')
plt.show()

lsr = np.loadtxt('lsr.csv').flatten()
lsr = np.unique(lsr)
indices = indices[diff!=0]
pt = pt[diff!=0]

plt.figure()

plt.scatter(indices, pt, s=0.3)

plt.scatter(indices[np.isin(pt,lsr)], pt[np.isin(pt,lsr)], s=0.4, label='Right shifts (LSR)', color='r')
plt.axhspan(0, balanced_ashr[1], label='Balanced Operators', color='C2', alpha=0.1)

plt.legend()
plt.xlabel('Time')
plt.ylabel('Line in assembly file')
plt.show()

indices = indices[np.isin(pt,lsr,invert=True)]
pt = pt[np.isin(pt,lsr,invert=True)]
ldr = np.loadtxt('ldr.csv').flatten()
ldr = np.unique(ldr)
mov = np.loadtxt('mov.csv').flatten()
mov = np.unique(mov)

plt.figure()

plt.scatter(indices, pt, s=0.3, label='Remaining imbalances')
plt.scatter(indices[np.isin(pt,ldr)], pt[np.isin(pt,ldr)], s=0.3, label='Load instructions')
plt.scatter(indices[np.isin(pt,mov)], pt[np.isin(pt,mov)], s=0.3, label='Move instructions')

plt.legend()
plt.xlabel('Time')
plt.ylabel('Line in assembly file')
plt.show()

remaining_filter = np.logical_and(np.isin(pt, ldr, invert=True), np.isin(pt,mov, invert=True))
pt = pt[remaining_filter]
indices = indices[remaining_filter]

plt.figure()

plt.scatter(indices, pt, s=0.3,label='Remaining imbalances')

plt.axhspan(balanced_and[0], balanced_and[1], label='balanced_and', color='C1', alpha=0.2)
plt.axhspan(balanced_mul[0], balanced_mul[1], label='balanced_mul', color='C2', alpha=0.2)
plt.axhspan(balanced_c_entry[0], balanced_c_entry[1], label='balanced_c_entry', color='C3', alpha=0.2)

plt.legend()
plt.xlabel('Trace point')
plt.ylabel('Line in assembly file')
plt.show()
