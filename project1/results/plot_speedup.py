import matplotlib.pyplot as plt
import pandas as pd

# Load CSV file containing thread counts and speedups
df = pd.read_csv("times.csv")

# Plotting Speedup vs Thread Count
plt.figure(figsize=(8, 5))
plt.plot(df["threads"], df["speedup"], marker='o', linestyle='-', color='green')
plt.title("Speedup vs Thread Count (Binary Search)")
plt.xlabel("Number of Threads")
plt.ylabel("Speedup (Sequential Time / Parallel Time)")
plt.grid(True)
plt.xticks(df["threads"])
plt.tight_layout()
plt.savefig("speedup_plot.png")
plt.show()
