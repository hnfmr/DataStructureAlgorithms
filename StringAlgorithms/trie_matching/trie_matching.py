# python3
import sys


def outgoing_edge(tree, current_node, symbol):
	edges = tree.get(current_node)
	if edges is not None:
		return edges.get(symbol)
	return None


def build_trie(patterns):
	tree = dict()
	# write your code here
	root = 0
	tree[root] = dict()
	max_node = 0
	for pattern in patterns:
		current_node = root
		for current_symbol in pattern:
			edge = outgoing_edge(tree, current_node, current_symbol)
			if edge is not None:
				current_node = tree[current_node][current_symbol]
			else:
				symbols = tree.get(current_node)
				if symbols is not None:
					symbols[current_symbol] = max_node + 1
				else:
					tree[current_node] = dict()
					tree[current_node][current_symbol] = max_node + 1
				current_node = max_node + 1
				max_node = current_node
	return tree


NA = -1


class Node:
	def __init__(self):
		self.next = [NA] * 4


def is_leaf(node, tree):
	children = tree.get(node)
	return children is None


def find_edge(tree, node, symbol):
	v_list = tree.get(node)
	if v_list is None:
		return None

	for val in v_list:
		if symbol is val:
			return tree[node][val]
	return None


def prefix_trie_matching(text, tree):
	symbol_pos = 0
	node = 0
	pat_found = False
	while symbol_pos < len(text):
		symbol = text[symbol_pos]
		edge = find_edge(tree, node, symbol)
		if edge is not None:
			node = edge
		else:
			break
		symbol_pos += 1

	if is_leaf(node, tree) is True:
		pat_found = True

	return pat_found


def solve(text, n, patterns):
	tree = build_trie(patterns)

	result = []

	txt = text

	offset = 0

	while len(txt) > 0:
		pat_found = prefix_trie_matching(txt, tree)
		if pat_found is True:
			result.append(offset)

		txt = txt[1:]
		offset += 1

	return result

text = sys.stdin.readline().strip()
n = int(sys.stdin.readline().strip())
patterns = []
for i in range(n):
	patterns += [sys.stdin.readline().strip()]

ans = solve(text, n, patterns)

sys.stdout.write(' '.join(map(str, ans)) + '\n')