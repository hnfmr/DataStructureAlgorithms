# python3
import sys


def outgoing_edge(tree, current_node, symbol):
	node_pair = tree.get(current_node)
	if node_pair is not None:
		return node_pair[1].get(symbol)
	return None


def build_trie(patterns):
	tree = dict()
	# write your code here
	root = 0
	tree[root] = (False, dict())
	max_node = 0
	for pattern in patterns:
		current_node = root
		for idx in range(len(pattern)):
			current_symbol = pattern[idx]
			edge = outgoing_edge(tree, current_node, current_symbol)
			if edge is not None:
				current_node = tree[current_node][1][current_symbol]
			else:
				node_pair = tree.get(current_node)
				if node_pair is not None:
					node_pair[1][current_symbol] = max_node + 1
				else:
					tree[current_node] = (False, dict())
					tree[current_node][1][current_symbol] = max_node + 1
				current_node = max_node + 1
				max_node = current_node
		tree[current_node] = (True, dict())

	return tree

NA = -1


class Node:
	def __init__(self):
		self.next = [NA] * 4


# True only if node exists and children container is empty
def is_leaf(node, tree):
	return tree[node][0] is True and len(tree[node][1]) is 0


def find_edge(tree, node, symbol):
	node_pair = tree.get(node)
	if node_pair is not None:
		v_list = node_pair[1]
		for val in v_list:
			if symbol is val:
				return node_pair[1][val]
	return None


def is_pattern(node, tree):
	node_pair = tree.get(node)
	if node_pair:
		return node_pair[0]
	return False


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

	if is_leaf(node, tree):
		pat_found = True
	elif is_pattern(node, tree):
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

# tree=build_trie(['ATCG', 'GGGT'])
# text='AATCGGGTTCAATCGGGGT'
# txt=text
# txt=txt[1:]
# a=prefix_trie_matching(txt, tree)
