import pygame
import node

WIDTH = 800
ROW_COLS = 20
NODE_SIZE = WIDTH // ROW_COLS

pygame.init()
WIN = pygame.display.set_mode((WIDTH, WIDTH))
pygame.display.set_caption("A* Pathfinding Visualization")

start_node = None
end_node = None

def main():
    grid = init_grid()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return

            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = get_clicked_pos()
                if event.button == 1:  # Left click
                    paint_node_with_mouse(mouse_pos, grid)
                elif event.button == 3:  # Right click
                    erase_node_with_mouse(mouse_pos, grid)

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_r:
                    grid = init_grid()

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE and start_node and end_node:
                    a_star_algorithm(start_node, end_node, grid)
                    
        WIN.fill((255, 255, 255))
        draw_grid(grid)
        pygame.display.update()

###

# Function to initialize the grid with Node instances and set neighbors
def init_grid():
    grid = []
    global start_node, end_node
    start_node = None
    end_node = None
    for i in range(ROW_COLS):
        row = []
        for j in range(ROW_COLS):
            node_instance = node.Node(i, j)
            row.append(node_instance)
        grid.append(row)

    for row in grid:
        for node_instance in row:
            x, y = node_instance.get_pos()
            if x < ROW_COLS - 1:
                node_instance.neighbors.append(grid[x + 1][y])
            if x > 0:
                node_instance.neighbors.append(grid[x - 1][y])
            if y < ROW_COLS - 1:
                node_instance.neighbors.append(grid[x][y + 1])
            if y > 0:
                node_instance.neighbors.append(grid[x][y - 1])
    
    return grid

# Function to draw the grid and nodes
def draw_grid(grid):
    for row in grid:
        for node in row:
            pygame.draw.rect(WIN, node.color, (node.x * NODE_SIZE, node.y * NODE_SIZE, NODE_SIZE, NODE_SIZE))
    
    for i in range(ROW_COLS+1):
        pygame.draw.line(WIN, (200, 200, 200), (i * NODE_SIZE, 0), (i * NODE_SIZE, WIDTH))
        pygame.draw.line(WIN, (200, 200, 200), (0, i * NODE_SIZE), (WIDTH, i * NODE_SIZE))

    pygame.display.update()

# Function to get grid position from mouse click
def get_clicked_pos():
    x, y = pygame.mouse.get_pos()
    row = x // NODE_SIZE
    col = y // NODE_SIZE
    return row, col

# Functions to handle painting and erasing nodes with mouse
def paint_node_with_mouse(mouse_pos, grid):
    global start_node, end_node
    row, col = mouse_pos
    node = grid[row][col]
    if node.color == node.COLORS['WHITE']:
        if start_node is None:
            node.set_node_type('start')
            start_node = node
        elif end_node is None:
            node.set_node_type('end')
            end_node = node
        else:
            node.set_node_type('wall')

def erase_node_with_mouse(mouse_pos, grid):
    global start_node, end_node
    row, col = mouse_pos
    node = grid[row][col]
    if node.color == node.COLORS['RED']:
        start_node = None
    elif node.color == node.COLORS['GREEN']:
        end_node = None
    node.set_node_type('empty')

# Manhattan distance heuristic
def heuristic(a, b):
    return abs(a.x - b.x) + abs(a.y - b.y)

# A * Algorithm Implementation
def a_star_algorithm(start, end, grid):
    open_set = []
    open_set.append(start)
    start.g = 0
    start.h = heuristic(start, end)
    start.f = start.h

    came_from = {}

    while open_set:
        current = min(open_set, key=lambda node: node.f)

        if current == end:
            reconstruct_path(came_from, end, grid)
            return True

        open_set.remove(current)

        for neighbor in current.neighbors:
            if neighbor.color == node.Node.COLORS['BLACK']:
                continue

            tentative_g = current.g + 1

            if tentative_g < neighbor.g:
                came_from[neighbor] = current
                neighbor.g = tentative_g
                neighbor.h = heuristic(neighbor, end)
                neighbor.f = neighbor.g + neighbor.h

                if neighbor not in open_set:
                    open_set.append(neighbor)
                    if neighbor.color != node.Node.COLORS['GREEN']:
                        neighbor.set_node_type('open')

        if current.color != node.Node.COLORS['RED']:
            current.set_node_type('closed')

        draw_grid(grid)
        pygame.display.update()

    return False

def reconstruct_path(came_from, current, grid):
    while current in came_from:
        current = came_from[current]
        if current.color != node.Node.COLORS['RED']:
            current.set_node_type('path')
            draw_grid(grid)
            pygame.display.update()

if __name__ == "__main__":
    main()

