import struct
import numpy as np
import matplotlib.pyplot as plt
import sys

NAME = "reflectogram_"
POSTFIX = ".bin"

arr = np.zeros((200, 2433))


def read_write_bins(path: str):
    for i in range(1, 200):
        arr[i - 1] = np.fromfile(path + NAME + str(i) + POSTFIX, dtype=np.int16)


def read_bin_write_txt(bin_filename, txt_filename):
    data = np.fromfile(bin_filename, dtype=np.int16)
    plt.plot(data)
    plt.savefig("graphout.png")
    np.savetxt("output.txt", data, delimiter=" ", fmt="%.2f")

# read_bin_write_txt("./src/build/debug/reflectogram_1.bin", "reflectogram.txt")

read_write_bins(sys.argv[1])
plt.imshow(arr.T, cmap="bwr", aspect="auto")
plt.savefig("imshow.png")