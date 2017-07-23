import os
import glob
import matplotlib.pyplot as plt
import math

styles = {'node': "bo", 'real': "rs", 'anchor': "^g", 'line':"b,-"}

class Instance:
    def __init__(self, file):
        self.nodes = []
        self.anchors = []
        f = open('instancias/loc/'+file+'_loc.txt', 'r')
        self.file = file
        inst = f.read()
        inst = inst.split('\n')
        self.start = float(inst[0])
        self.end = float(inst[1])
        self.n_nodes = int(inst[2])
        self.n_anchors = int(inst[3])
        self.signal_range = float(inst[4])
        self.erro = float(inst[5])
        inst = inst[6:]

        for i in range(self.n_anchors):
            inst[i] = inst[i].split()

        for i in range(self.n_anchors):
            n = Node(i, [float(inst[i][0]), float(inst[i][1])], 0)
            self.anchors.append(n)

        for i in range(self.n_nodes):
            n = Node(i, [0, 0], 1)
            self.nodes.append(n)


        inst = inst[self.n_anchors:]
        inst.remove('')


        for i in range(self.n_anchors):
            inst[i] = inst[i].split()
            inst[i] = inst[i][1:]
            range_j = int(len(inst[i])/2) - 1
            for j in range(range_j):
                pos_n = int(inst[i][j*2])
                dist = float(inst[i][j*2+1])
                self.anchors[i].add_neighbor(self.nodes[pos_n], dist)
                self.nodes[pos_n].add_neighbor(self.anchors[i], dist)

        inst = inst[self.n_anchors:]

        for i in range(self.n_nodes):
            inst[i] = inst[i].split()
            inst[i] = inst[i][1:]
            range_j = int(len(inst[i]) / 2) - 1
            for j in range(range_j):
                pos_n = int(inst[i][j*2])
                dist = float(inst[i][j*2+1])
                self.nodes[i].add_neighbor(self.nodes[pos_n], dist)
                self.nodes[pos_n].add_neighbor(self.nodes[i], dist)

class Node:
    def __init__(self, id, pos, type):
        self.id = id
        self.pos = pos
        self.type = type
        self.neighbors = [[], []]


    def add_neighbor(self, neighbor, dist):
        self.neighbors[neighbor.type].append([neighbor, dist])

def chose_inst():
    inst = [x.replace("instancias/result/", '').replace("_result.txt", '') for x in glob.glob("instancias/result/*.txt")]
    
    while True:
        test = []
        chosen = input("Instancia: ")
        for i in inst:
            if i == chosen:
                os.system('cls' if os.name == 'nt' else 'clear')
                return i
            if chosen in i:
                test.append(i)

        
        os.system('cls' if os.name == 'nt' else 'clear')
        
        print("Instancia não encontrada.")
        if test:
            print("Instancias com nome similar:")
            for i in test:
                print(i)
            print("Escolha uma das instancias acima:")
        else:
            print("Escolha qual instancia será mostrada: ")


def read(instance_name):
    f = open('instancias/rede/' + instance_name + '_rede.txt', 'r')
    rede = f.read().split("\n")

    n_anchors = int(rede[0])
    n_nodes = int(rede[1])
    rede = rede[3:]
    rede.pop()

    for i in range(n_nodes+n_anchors):
        rede[i] = rede[i].split()[1:]
        rede[i] = (float(rede[i][0]), float(rede[i][1]))

    f = open('instancias/result/' + instance_name + '_result.txt', 'r')

    result = f.read().split("\n")
    result.pop()

    for i in range(n_nodes):
        result[i] = result[i].split()
        result[i] = (float(result[i][0]), float(result[i][1]))


    return rede, result


def show_i(result_x, result_y, real_x, real_y):
    fig = plt.figure()
    ax = fig.add_subplot(111)

    ax.plot(result_x, result_y, styles['node'], fillstyle="none")

    n_anchors = len(real_x) - len(result_x)

    ax.plot(real_x[:n_anchors], real_y[:n_anchors], styles['anchor'], fillstyle="none")

    ax.plot(real_x[n_anchors:], real_y[n_anchors:], styles['real'], fillstyle="none")



    zip_coord_x = list(zip(real_x[n_anchors:], result_x))
    zip_coord_y = list(zip(real_y[n_anchors:], result_y))

    for i in range(len(zip_coord_x)):
        ax.plot(zip_coord_x[i], zip_coord_y[i], styles['line'])

    i = 0
    for xy in zip(result_x, result_y):
        ax.annotate(str(i), xy=xy, textcoords='data')
        i += 1

    return fig


def figure(rede, result):
    l_x = []
    l_y = []
    for i in result:
        l_x.append(i[0])
        l_y.append(i[1])

    r_x = []
    r_y = []
    for i in rede:
        r_x.append(i[0])
        r_y.append(i[1])

    return show_i(l_x, l_y, r_x, r_y)


def set_node_on_fig(node, fig):
    fig.clf()
    ax = fig.add_subplot(111, aspect='equal')
    ax.axis([0, 1, 0 , 1])

    ax.plot(node.pos[0], node.pos[1], 'or', fillstyle='none')
    ax.annotate(str(node.id), xy=node.pos, textcoords='data')

    l_x = []
    l_y = []
    id = []

    for edge in node.neighbors[0]:
        l_x.append(edge[0].pos[0])
        l_y.append(edge[0].pos[1])
        id.append(edge[0].id)
        e = plt.Circle(xy=[edge[0].pos[0], edge[0].pos[1]], radius=edge[1], facecolor='none', edgecolor='g')
        ax.add_artist(e)

    for i in range(len(id)):
        ax.annotate(str(id[i]), xy=[l_x[i], l_y[i]], textcoords='data')

    l_x += [0, 1]
    l_y += [0, 1]
    ax.plot(l_x, l_y, styles['anchor'], fillstyle='none')

    l_x = []
    l_y = []
    id = []
    for edge in node.neighbors[1]:
        l_x.append(edge[0].pos[0])
        l_y.append(edge[0].pos[1])
        id.append(edge[0].id)
        e = plt.Circle(xy=[edge[0].pos[0], edge[0].pos[1]], radius=edge[1], facecolor='none', edgecolor='b')
        ax.add_artist(e)

    ax.plot(l_x, l_y, styles['node'], fillstyle='none')

    for i in range(len(id)):
        ax.annotate(str(id[i]), xy=[l_x[i], l_y[i]], textcoords='data')
    
    ax.grid(True)
    fig.canvas.draw()

class Show_node:
    def __init__(self, click, des, nodes):
        self.des = des
        self.click = click
        self.cid = click.canvas.mpl_connect('button_press_event', self)
        self.nodes = nodes

    def dist(self, p_a, p_b):
        x = p_a[0] - p_b[0]
        y = p_a[1] - p_b[1]

        if x == 0 and y == 0:
            return 0

        return math.sqrt(x * x + y * y)

    def __call__(self, event):
        n = self.nodes[0]
        xy = [event.xdata, event.ydata]
        for p in xy:
            if p == None: return
        for node in self.nodes:
            if self.dist(n.pos, xy) > self.dist(node.pos, xy):
                n = node
        print('Node: ', n.id, n.pos)
        set_node_on_fig(n, self.des)

if __name__ == "__main__":
    os.system('cls' if os.name == 'nt' else 'clear')
    instance = Instance(chose_inst())

    rede, result = read(instance.file)

    for i in range(instance.n_nodes):
        instance.nodes[i].pos = result[i]

    fig = figure(rede, result)
    fig2 = plt.figure()
    plt.grid(True)
    sh = Show_node(fig, fig2, instance.nodes)

    plt.show()