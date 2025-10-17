#!/usr/bin/env python3
import sys
import re

if len(sys.argv) > 1:
    with open(sys.argv[1], 'r', encoding='utf-8') as f:
        text = f.read()
else:
    text = sys.stdin.read()

# Normalize punctuation and spaces
text = text.replace('：', ':').replace(' ', ' ').replace('\u00a0', ' ')  # full-width colon, narrow no-break space, etc.

# Find numbers following ": "
pattern = re.compile(r':\s*([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?)')
matches = pattern.findall(text)
numbers = [float(m) for m in matches]

print("count:", len(numbers))
print("sum:  {:.12f}".format(sum(numbers)))