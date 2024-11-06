#!/usr/bin/env python3


import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Read the CSV files
data = pd.read_csv('before.csv')

sns.barplot(x='counter', y='value', hue='type', data=data)

# Add labels and title
plt.xlabel('Counter')
plt.ylabel('Value')
plt.title('Comparison of Values Before and After')
plt.legend()

# Better readability
plt.xticks(rotation=45)
plt.tight_layout()

# Save the plot to a file
plt.savefig('comparison_plot.pdf')

# Logarithmic scale
plt.figure(figsize=(10, 6))
sns.barplot(x='counter', y='value', hue='type', data=data)
plt.yscale('log')

# Add labels and title
plt.xlabel('Counter')
plt.ylabel('Value (Log Scale)')
plt.title('Comparison of Values Before and After (Log Scale)')
plt.legend()

# Better readability
plt.xticks(rotation=45)
plt.tight_layout()

# Save the plot to a file
plt.savefig('comparison_plot_log.pdf')