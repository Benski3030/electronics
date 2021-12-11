
# coding: utf-8

# In[ ]:

import pandas as pd
import matplotlib.pyplot as plt
get_ipython().magic(u'matplotlib inline')
get_ipython().magic(u'pylab inline')


# In[ ]:

streamtemp = pd.read_csv(r"C:\Users\foo\temps.csv", names = ["time","tempfar"])
streamtemp["time"] = pd.to_datetime(streamtemp["time"])
streamtemp = streamtemp.ix[1:]


# In[ ]:

streamtemp


# In[ ]:

pylab.rcParams['figure.figsize'] = (20, 10)
streamtemp.plot(x = "time", y = "tempfar")
plt.title("Temperature in Degrees Fahrenheit")
plt.ylabel("Degrees Fahrenheit")
plt.xlabel("Time of Day")
plt.grid(True)
plt.show()


# In[ ]:



