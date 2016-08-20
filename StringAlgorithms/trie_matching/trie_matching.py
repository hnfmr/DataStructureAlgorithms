# python3
import sys

def outgoing_edge(tree, current_node, symbol):
    edges = tree.get(current_node)
    if edges != None:
        return edges.get(symbol)
    else:
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
            if edge != None:
                current_node = tree[current_node][current_symbol]
            else:
                symbols = tree.get(current_node)
                if symbols != None:
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


def solve(text, n, patterns):
    tree = build_trie(patterns)

    result = []

    

    return result


text = sys.stdin.readline().strip()
n = int(sys.stdin.readline().strip())
patterns = []
for i in range(n):
    patterns += [sys.stdin.readline().strip()]

ans = solve(text, n, patterns)

sys.stdout.write(' '.join(map(str, ans)) + '\n')
