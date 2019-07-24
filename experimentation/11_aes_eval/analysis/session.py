# coding: utf-8
different = t1 != t2
different.shape
different.sum()
s1 = t1[different]
s2 = t2[different]
diff = s1-s2
min(diff)
hw = np.vectorize(hamming_weight)
d = hw(diff)
hw1 = hw(s1)
hw2 = hw(s2)
diff = hw1-hw2
min(diff)
max(diff)
import matplotlib.pyplot as plt
diff.shape
udm = ut1 != ut2
us1 = ut1[udm]
us2 = ut2[udm]
uhw1 = hw(us1)
uhw2 = hw(us2)
udiff = uhw1 -uhw2
plt.scatter(range(diff.shape[0]), diff)
get_ipython().run_line_magic('', 'save session.py ~0/')
get_ipython().run_line_magic('save', 'session.py ~0/')
