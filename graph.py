import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


if __name__ == "__main__":
    #fig, (ax1, ax2) = plt.subplots(1, 2)
    fig, ax1 = plt.subplots()

    df1 = pd.read_csv(sys.argv[1])
    ax1.plot(df1['n'].values, df1['time'].values, label=sys.argv[1])

    if len(sys.argv) > 2:
        df2 = pd.read_csv(sys.argv[2])
        ax1.plot(df2['n'].values, df2['time'].values, label=sys.argv[2])
   # ax2.plot(df2['n'].values, df2['time'].values, label=sys.argv[2])
    fig.legend()
    plt.show()
