import matplotlib.pyplot as plt
import numpy as np

n = np.arange(1, 21, dtype=np.float64)
custo_guloso = n * np.log2(n)
custo_dinamico = n**2
custo_forca_bruta = 2**n

plt.figure(figsize=(12, 8))
plt.plot(n, custo_guloso, label='O(n log n) - Algoritmo Guloso', color='blue', marker='o')
plt.plot(n, custo_dinamico, label='O(n^2) - Programação Dinâmica', color='green', marker='s')
plt.plot(n, custo_forca_bruta, label='O(2^n) - Força Bruta', color='red', marker='^')
plt.ylim(0, 500)
plt.title("Comparação das Complexidades dos Algoritmos", fontsize=16)
plt.xlabel("Tamanho da Entrada (n)", fontsize=12)
plt.ylabel("Número de Operações", fontsize=12)
plt.legend()
plt.grid(True, linestyle='--')
plt.xticks(n)
plt.show()