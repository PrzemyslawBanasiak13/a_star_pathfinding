import pygame
import node

WIDTH, HEIGHT = 800, 600
ROW_COLS = 20
NODE_SIZE = WIDTH // ROW_COLS

pygame.init()
WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("A* Pathfinding Visualization")

start_exist = False
end_exist = False

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
                    reset_grid(grid)

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    pass  # Placeholder for starting the A* algorithm

        WIN.fill((255, 255, 255))
        draw_grid(grid)
        pygame.display.update()

###

# Function to initialize the grid with Node instances and set neighbors
def init_grid():
    grid = []
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
        pygame.draw.line(WIN, (200, 200, 200), (i * NODE_SIZE, 0), (i * NODE_SIZE, HEIGHT))
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
    global start_exist, end_exist
    row, col = mouse_pos
    node = grid[row][col]
    if node.color == node.COLORS['WHITE']:
        if not start_exist:
            node.set_node_type('start')
            start_exist = True
        elif not end_exist:
            node.set_node_type('end')
            end_exist = True
        else:
            node.set_node_type('wall')

def erase_node_with_mouse(mouse_pos, grid):
    global start_exist, end_exist
    row, col = mouse_pos
    node = grid[row][col]
    if node.color == node.COLORS['RED']:
        start_exist = False
    elif node.color == node.COLORS['GREEN']:
        end_exist = False
    node.set_node_type('empty')

def reset_grid(grid):
    global start_exist, end_exist
    for row in grid:
        for node in row:
            node.set_node_type('empty')
    start_exist = False
    end_exist = False
