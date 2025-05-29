import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("times.csv")

plt.figure(figsize=(8, 5))
plt.plot(df["threads"], df["average_time_microseconds"], marker='o', linestyle='-', color='navy')
plt.title("Average Binary Search Time vs Thread Count (1000 Element)")
plt.xlabel("Number of Threads")
plt.ylabel("Average Time (microseconds)")
plt.grid(True)
plt.xticks(df["threads"])
plt.tight_layout()
plt.savefig("performance_plot.png")
plt.show()
