import re


with open("input.txt", "r") as f:
	file_str = f.read()

def to_nums(s : str):
	r = s[4:-1].split(',')
	return int(r[0]), int(r[1])

all_mul = re.findall('don\'t\(\)|do\(\)|mul\(\d+,\d+\)', file_str)

ans = 0
is_do = True

for op in all_mul:
	if op == "don\'t()":
		is_do = False
	elif op == "do()":
		is_do = True
	elif is_do:
		x, y = to_nums(op)
		ans += x * y

print(f"Answer {ans}")