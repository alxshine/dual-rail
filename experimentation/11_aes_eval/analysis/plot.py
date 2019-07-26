# coding: utf-8
import numpy as np
import matplotlib.pyplot as plt
import csv

def hamming_weight(v):
    ret = 0
    for i in range(32):
        ret += v&1
        v >>= 1
    return ret
hw = np.vectorize(hamming_weight)

t1 = np.load('reworked_001.npy')
t2 = np.load('reworked_002.npy')

pc_trace = []
pc_file = open('pc.log')
for row in csv.reader(pc_file):
    pc_trace.append(int(row[0]))
pt = np.array(pc_trace)

# %load boundaries.py
balanced_2_1 = [53, 73]
balanced_int = [87, 105]
balanced_int_wide = [119, 130]
unbalanced_int = [144, 150]
balanced_and = [164, 195]
balanced_xor = [209, 250]
balanced_add = [264, 281]
balanced_sub = [295, 315]
balanced_negative = [329, 346]
balanced_mul = [360, 390]
balanced_sdiv = [404, 466]
balanced_srem = [480, 547]
balanced_shl = [561, 580]
balanced_lshr = [594, 614]
balanced_ashr = [628, 643]
balanced_ECB_encrypt = [657, 742]
balanced_BlockCopy = [759, 828]
balanced_KeyExpansion = [841, 1660]
balanced_Cipher = [1677, 1764]
balanced_AddRoundKey = [1777, 1943]
balanced_SubBytes = [1956, 2030]
balanced_ShiftRows = [2043, 2200]
balanced_MixColumns = [2213, 2808]
balanced_xtime = [2821, 2881]
decryption_start = 2894

enc_len = 489075
pt = pt[:enc_len]
indices = np.arange(enc_len)[pt<decryption_start]
pt = pt[indices]
t1 = t1[indices]
t2 = t2[indices]

plt.scatter(indices, pt, s=0.3, label='Program Counter')
plt.axhspan(balanced_BlockCopy[0],balanced_BlockCopy[1], label='BlockCopy', color='C2', alpha=0.2)
plt.axhspan(balanced_KeyExpansion[0],balanced_KeyExpansion[1],label='KeyExpansion',color='C3', alpha=0.2)
plt.axhspan(balanced_Cipher[0],balanced_Cipher[1],label='Cipher',color='C4',alpha=0.2)
plt.axhspan(balanced_AddRoundKey[0],balanced_AddRoundKey[1],label='AddRoundKey',color='C5', alpha=0.2)
plt.axhspan(balanced_SubBytes[0],balanced_SubBytes[1],label='SubBytes', color='C6', alpha=0.2)
plt.axhspan(balanced_ShiftRows[0],balanced_ShiftRows[1],label='ShiftRows',color='C7',alpha=0.2)
plt.axhspan(balanced_MixColumns[0],balanced_MixColumns[1],label='MixColumns',color='C8',alpha=0.2)
plt.axhspan(balanced_xtime[0],balanced_xtime[1],label='xtime', color='C9', alpha=0.2)
plt.legend()
plt.show()
