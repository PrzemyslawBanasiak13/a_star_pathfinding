class Node:
    __slots__ = ('x', 'y', 'color', 'neighbors', 'g', 'h', 'f')

    # Colors
    COLORS = {
        'WHITE': (255, 255, 255),
        'BLACK': (0, 0, 0),
        'RED': (255, 0, 0),
        'GREEN': (0, 255, 0),
        'PURPLE': (128, 0, 128),  
        'ORANGE': (255, 165, 0),
        'YELLOW': (255, 255, 0)
    }

    NODE_TYPE_TO_COLOR = {
    'empty': COLORS['WHITE'],
    'wall': COLORS['BLACK'],
    'start': COLORS['RED'],
    'end': COLORS['GREEN'],
    'path': COLORS['PURPLE'],
    'open': COLORS['ORANGE'],
    'closed': COLORS['YELLOW']
    }

    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y
        self.color = Node.COLORS['WHITE']
        self.neighbors = []
        self.g = float('inf')
        self.h = float('inf')
        self.f = float('inf')

    def get_pos(self) -> tuple[int, int]:
        return self.x, self.y

    def get_node_type(self) -> str:
        return Node.COLOR_TO_NODE_TYPE.get(self.color, 'unknown')

    def set_node_type(self, node_type: str):
        self.color = Node.NODE_TYPE_TO_COLOR.get(node_type, Node.COLORS['WHITE'])





