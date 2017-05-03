import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

csv=pd.read_csv("RSA2.csv",names=["Threads","Serial","Parallel"])

xx=list(csv.Threads)
yy1=list(csv.Serial)
yy2=list(csv.Parallel)
xx=xx[1:]
yy1=yy1[1:]
yy2=yy2[1:]
yy1=map(float,yy1)
yy2=map(float,yy2)
xxx1=np.arange(len(yy1))
xxx2=np.arange(len(yy2))
fig=plt.figure()

figg1=fig.add_subplot(111)
figg2=fig.add_subplot(111)


figg1.bar(xxx1,yy1)
figg2.bar(xxx2,yy2)
plt.xlabel("Threads")
plt.ylabel("Time(microseconds)")

figg1.set_xticks(xxx1)
figg1.set_xticklabels(xx)
figg1.set_yticks(range(0,max(yy1)+1))

figg2.set_xticks(xxx2)
figg2.set_xticklabels(xx)
figg2.set_yticks(range(0,max(yy2)+1))

plt.savefig("Graph.png")