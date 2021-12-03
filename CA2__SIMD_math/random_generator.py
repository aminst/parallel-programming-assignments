import numpy as np
import sys

if len(sys.argv) < 2:
    print('Usage: python3 random_generator.py <exponent>')
    exit(0)

n = 2 ** int(sys.argv[1])
a = np.random.uniform(low=-1e2, high=1e2, size=n)

print(n)
for x in a:
    print(x, end=' ')
print()
