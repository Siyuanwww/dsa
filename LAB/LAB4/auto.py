from graphviz import Digraph

# g = Digraph('1')
# g.attr('graph', rankdir='LR')
# g.edge('0', '1', label='a')
# g.edge('1', '2', label='a')
# g.edge('2', '3', label='a')
# g.edge('1', '0', label='^a')
# g.edge('2', '0', label='^a')
# g.edge('3', '0', label='^a')
# g.edge('0', '0', label='^a')

# g = Digraph('2')
# g.attr('graph', rankdir='LR')
# g.edge('0', '1', label='a')
# g.edge('1', '2', label='b')
# g.edge('2', '3', label='a')
# g.edge('3', '4', label='b')
# g.edge('4', '5', label='a')
# g.edge('5', '6', label='c')
# g.edge('1', '1', label='a')
# g.edge('1', '0', '^a^b')
# g.edge('2', '0', '^a')
# g.edge('3', '1', 'a')
# g.edge('3', '0', '^a^b')
# g.edge('4', '2', 'b')
# g.edge('4', '0', '^a^b')
# g.edge('5', '3', 'a')
# g.edge('5', '0', '^a^c')
# g.edge('6', '1', 'a')
# g.edge('6', '0', '^a')


g = Digraph('test')
g.node('a', shape='doublecircle')
g.format = 'svg'

# g.edges([('a0', 'a1'), ('a1', 'a2')])
# g.edge('a2', 'a3', label='fuck')
# g.edge('a3', 'a0')


g.render(directory='output')
# g.view()