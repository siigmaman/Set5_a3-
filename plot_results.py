import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('data/results.csv')

plt.figure(figsize=(10,6))
plt.plot(df['Step'], df['Ft0'], label='Ft0 (точное)', marker='o')
plt.plot(df['Step'], df['Nt'], label='Nt (HyperLogLog)', marker='x')
plt.xlabel('Шаг обработки потока (%)')
plt.ylabel('Количество уникальных элементов')
plt.title('Сравнение Ft0 и Nt')
plt.legend()
plt.grid(True)
plt.savefig('results/Ft0_vs_Nt.png')
plt.show()

E_Nt = df['Nt']
sigma_Nt = [0.0]*len(E_Nt)

plt.figure(figsize=(10,6))
plt.plot(df['Step'], E_Nt, label='E(Nt)', color='blue')
plt.fill_between(df['Step'], E_Nt - sigma_Nt, E_Nt + sigma_Nt, color='blue', alpha=0.2, label='± σNt')
plt.xlabel('Шаг обработки потока (%)')
plt.ylabel('Оценка уникальных элементов')
plt.title('Среднее значение Nt и область неопределенности')
plt.legend()
plt.grid(True)
plt.savefig('results/E_Nt_sigma.png')
plt.show()