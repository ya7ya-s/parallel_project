import pandas as pd
import matplotlib.pyplot as plt

# Load CSV (Excel can open this too)
df = pd.read_csv("speedup_results.csv")

# Plot
plt.figure(figsize=(8, 6))
plt.plot(df['Threads'], df['Speedup'], marker='o', label='Observed Speedup')
plt.plot(df['Threads'], df['Threads'], linestyle='--', label='Ideal Speedup', color='gray')

plt.xlabel("Number of Threads")
plt.ylabel("Speedup")
plt.title("Speedup vs Threads for Binary Search")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
