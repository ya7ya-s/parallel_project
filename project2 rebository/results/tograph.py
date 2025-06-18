import pandas as pd
import matplotlib.pyplot as plt

# Read CSV
df = pd.read_csv("results.csv")

# Plotting
plt.figure(figsize=(8, 5))
plt.plot(df['Threads'], df['AverageTime'], marker='o', linestyle='-', color='orange')

plt.title('Binary Search Execution Time vs Thread Count (OpenMP)')
plt.xlabel('Number of Threads')
plt.ylabel('Average Time (microseconds)')
plt.grid(True)
plt.xticks(df['Threads'])

# Save and show
plt.savefig("performance_plot.png")
plt.show()
