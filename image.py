import numpy as np
import matplotlib.pyplot as plt

image = np.random.normal(size=(250, 2500))


plt.imshow(image, aspect = "auto", cmap = "jet")
plt.savefig("image.png")
