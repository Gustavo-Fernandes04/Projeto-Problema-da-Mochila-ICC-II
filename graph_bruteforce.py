import matplotlib.pyplot as plt

x_valores = [5, 10, 20, 100, 500, 1000]
y_valores_bruteforce = [5e-6, 11e-6, 116e-6, 1e21, 1e141, 1e291]

#o grafico gerado tem a forma aproximada de nlog n, o que condiz com a complexidade do algoritmo guloso
plt.plot(x_valores, y_valores_bruteforce, marker='o', color='blue', label='guloso')
plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))
plt.title("Tempos de execução x numero de itens n", fontsize=16)
plt.ylabel("Tempo de execução (em segundos)", fontsize=12)
plt.xlabel("Numero de itens n", fontsize=12)
plt.grid(True)
plt.show()
