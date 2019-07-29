from boundaries import *
from load import *

indices = indices[pt<=balanced_ashr[1]]
pt = pt[pt<=balanced_ashr[1]]

plt.scatter(indices, pt, s=0.3)
plt.axhspan(balanced_1_2[0],balanced_1_2[1], label='balanced_1_2', color='C2', alpha=0.2)
plt.axhspan(balanced_2_1[0],balanced_2_1[1], label='balanced_2_1', color='C3', alpha=0.2)
plt.axhspan(balanced_int[0],balanced_int[1],label='balanced_int',color='C4', alpha=0.2)
plt.axhspan(unbalanced_int[0],unbalanced_int[1],label='unbalanced_int',color='C5', alpha=0.2)
plt.axhspan(balanced_and[0],balanced_and[1],label='balanced_and', color='C6', alpha=0.2)
plt.axhspan(balanced_xor[0],balanced_xor[1],label='balanced_xor',color='C7',alpha=0.2)
plt.axhspan(balanced_add[0],balanced_add[1],label='balanced_add',color='C8',alpha=0.2)
plt.axhspan(balanced_sub[0],balanced_sub[1],label='balanced_sub',color='C9',alpha=0.2)
plt.axhspan(balanced_mul[0],balanced_mul[1],label='balanced_mul',color='C10',alpha=0.2)
plt.axhspan(balanced_sdiv[0],balanced_sdiv[1],label='balanced_sdiv',color='C11',alpha=0.2)
plt.axhspan(balanced_srem[0],balanced_srem[1],label='balanced_srem',color='C12',alpha=0.2,hatch='//')
plt.axhspan(balanced_shl[0],balanced_shl[1],label='balanced_shl',color='C13',alpha=0.2,hatch='//')
plt.axhspan(balanced_lshr[0],balanced_lshr[1],label='balanced_lshr',color='C14',alpha=0.2,hatch='//')
plt.axhspan(balanced_ashr[0],balanced_ashr[1],label='balanced_ashr',color='C15',alpha=0.2,hatch='//')

plt.legend()
plt.xlabel('Trace point')
plt.ylabel('Location in program')

plt.tight_layout()
plt.savefig('balanced-ops.png')
