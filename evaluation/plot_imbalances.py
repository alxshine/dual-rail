import matplotlib.pyplot as plt

from boundaries import *
from load import *

plt.figure()
plt.scatter(indices, pt, s=0.3)
plt.scatter(indices[diff != 0],
            pt[diff != 0],
            s=0.5,
            color='xkcd:orangered',
            label='Imbalances')

plt.axhspan(balanced_BlockCopy[0],
            balanced_xtime[1],
            label='AES',
            color='C0',
            alpha=0.15)
plt.axhspan(0,
            balanced_ashr[1],
            label='Balanced operators',
            color='C1',
            alpha=0.15)

plt.legend()
plt.xlabel('Time')
plt.ylabel('Location in program')
plt.tight_layout()
plt.savefig('imbalances-0.png')
# plt.show()

lsr = np.loadtxt('lsr.csv').flatten()
lsr = np.unique(lsr)
indices = indices[diff != 0]
pt = pt[diff != 0]

plt.figure()

plt.scatter(indices, pt, s=0.6, label='Imbalances')
plt.scatter(indices[np.isin(pt, lsr)],
            pt[np.isin(pt, lsr)],
            s=0.6,
            label='Right shifts (LSR)',
            color='xkcd:orangered')

plt.axhspan(balanced_lshr[0],
            balanced_lshr[1],
            label='balanced_lshr',
            color='C0',
            alpha=0.2)
plt.axhspan(balanced_2_1[0],
            balanced_2_1[1],
            label='balanced_2_1',
            color='C1',
            alpha=0.2)

plt.legend()
plt.xlabel('Time')
plt.ylabel('Location in program')
plt.tight_layout()
plt.savefig('imbalances-1.png')
# plt.show()

lsr = lsr[lsr >= balanced_ashr[1]]
indices = indices[np.isin(pt, lsr, invert=True)]
pt = pt[np.isin(pt, lsr, invert=True)]
ldr = np.loadtxt('ldr.csv').flatten()
ldr = np.unique(ldr)
mov = np.loadtxt('mov.csv').flatten()
mov = np.unique(mov)

plt.figure()

plt.scatter(indices, pt, s=1, label='Remaining imbalances')
plt.scatter(indices[np.isin(pt, ldr)],
            pt[np.isin(pt, ldr)],
            s=1,
            color='xkcd:orangered',
            label='Load instructions')
plt.scatter(indices[np.isin(pt, mov)],
            pt[np.isin(pt, mov)],
            s=1,
            color='black',
            label='Move instructions')

plt.legend()
plt.xlabel('Time')
plt.ylabel('Location in program')
plt.tight_layout()
plt.savefig('imbalances-2.png')
# plt.show()

remaining_filter = np.logical_or(
    np.logical_and(np.isin(pt, ldr, invert=True),
                   np.isin(pt, mov, invert=True)), pt == 119)
pt = pt[remaining_filter]
indices = indices[remaining_filter]

plt.figure()

plt.scatter(indices, pt, s=1, label='Remaining imbalances')

plt.axhspan(balanced_c_entry[0],
            balanced_c_entry[1],
            label='balanced_c_entry',
            color='C0',
            alpha=0.2)
plt.axhspan(balanced_lshr[0],
            balanced_lshr[1],
            label='balanced_lshr',
            color='C1',
            alpha=0.2)
plt.axhspan(balanced_mul[0],
            balanced_mul[1],
            label='balanced_mul',
            color='C0',
            alpha=0.2)
plt.axhspan(balanced_and[0],
            balanced_and[1],
            label='balanced_and',
            color='C1',
            alpha=0.2)
plt.axhspan(balanced_2_1[0],
            balanced_2_1[1],
            label='balanced_2_1',
            color='C0',
            alpha=0.2)

plt.legend()
plt.xlabel('Trace point')
plt.ylabel('Location in program')
plt.tight_layout()
plt.savefig('imbalances-3.png')
# plt.show()
