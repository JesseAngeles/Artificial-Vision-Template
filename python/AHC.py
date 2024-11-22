import json
from scipy.cluster.hierarchy import dendrogram
import matplotlib.pyplot as plt
import numpy as np

# Carga el archivo JSON
with open("./build/dendrogram_data.json", "r") as file:
    merge_data = json.load(file)

# Convierte la información en el formato adecuado
Z = np.array([[step["cluster_1"], step["cluster_2"], step["distance"], step["size"]] for step in merge_data])

# Grafica el dendrograma
plt.figure(figsize=(10, 5))
dendrogram(Z)
plt.title("Dendrogram")
plt.xlabel("Cluster")
plt.ylabel("Distance")
plt.show()
