from boundaries import *
from load import *

plt.scatter(indices, pt, s=0.3)
plt.axhspan(balanced_BlockCopy[0],balanced_BlockCopy[1], label='BlockCopy', color='C2', alpha=0.2)
plt.axhspan(balanced_KeyExpansion[0],balanced_KeyExpansion[1],label='KeyExpansion',color='C3', alpha=0.2)
plt.axhspan(balanced_Cipher[0],balanced_Cipher[1],label='Cipher',color='C4',alpha=0.2)
plt.axhspan(balanced_AddRoundKey[0],balanced_AddRoundKey[1],label='AddRoundKey',color='C5', alpha=0.2)
plt.axhspan(balanced_SubBytes[0],balanced_SubBytes[1],label='SubBytes', color='C6', alpha=0.2)
plt.axhspan(balanced_ShiftRows[0],balanced_ShiftRows[1],label='ShiftRows',color='C7',alpha=0.2)
plt.axhspan(balanced_MixColumns[0],balanced_MixColumns[1],label='MixColumns',color='C8',alpha=0.2)
plt.axhspan(balanced_xtime[0],balanced_xtime[1],label='xtime', color='C9', alpha=0.2)

plt.legend()
plt.xlabel('Trace point')
plt.ylabel('Line in assembly file')

plt.show()
