# Uses python3
import sys


def outgoing_edge(tree, current_node, symbol):
    edges = tree.get(current_node)
    if edges != None:
        return edges.get(symbol)
    else:
        return None


# Return the trie built from patterns
# in the form of a dictionary of dictionaries,
# e.g. {0:{'A':1,'T':2},1:{'C':3}}
# where the key of the external dictionary is
# the node ID (integer), and the internal dictionary
# contains all the trie edges outgoing from the corresponding
# node, and the keys are the letters on those edges, and the
# values are the node IDs to which these edges lead.
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


if __name__ == '__main__':
    patterns = sys.stdin.read().split()[1:]
    tree = build_trie(patterns)
    for node in tree:
        for c in tree[node]:
            print("{}->{}:{}".format(node, tree[node][c], c))
