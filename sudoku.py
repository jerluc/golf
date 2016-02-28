from math import sqrt

passing_board = [
  7, 5, 1,   8, 4, 3,   9, 2, 6,
  8, 9, 3,   6, 2, 5,   1, 7, 4,
  6, 4, 2,   1, 7, 9,   5, 8, 3,

  4, 2, 5,   3, 1, 6,   7, 9, 8,
  1, 7, 6,   9, 8, 2,   3, 4, 5,
  9, 3, 8,   7, 5, 4,   6, 1, 2,

  3, 6, 4,   2, 9, 7,   8, 5, 1,
  2, 8, 9,   5, 3, 1,   4, 6, 7,
  5, 1, 7,   4, 6, 8,   2, 3, 9
]

BOARD_WIDTH = 9

def rot90(board):
    new_board = []
    for i in range(len(board)):
        r, c = torc(i)
        new_index = getindex(BOARD_WIDTH - c - 1, r)
        new_board.append(board[new_index])
    return new_board

def rot180(board):
    return rot90(rot90(board))

def rot270(board):
    return rot180(rot90(board))

def torc(index):
    return index / BOARD_WIDTH, index % BOARD_WIDTH

def getindex(r, c):
    return (r * BOARD_WIDTH) + (c % BOARD_WIDTH)

def getcol(board, c):
    return [board[getindex(r, c)] for r in range(BOARD_WIDTH)]

def getrow(board, r):
    return [board[getindex(r, c)] for c in range(BOARD_WIDTH)]

def getregion(board, regionindex):
    region_width = int(sqrt(BOARD_WIDTH))
    x = regionindex / region_width
    y = regionindex % region_width
    rows = map(lambda c: getrow(board, y * region_width + c), range(3))
    rows = map(lambda row: row[x * region_width:(x + 1) * region_width], rows)
    return reduce(lambda l, r: l + r, rows)

def checkboard(board):
    for rowindex in range(3):
        assert len(set(getrow(board, rowindex))) == BOARD_WIDTH
    for colindex in range(3):
        assert len(set(getcol(board, colindex))) == BOARD_WIDTH
    for regionindex in range(9):
        assert len(set(getregion(board, regionindex))) == BOARD_WIDTH

if __name__ == '__main__':
    assert passing_board == rot90(rot270(passing_board))
    checkboard(passing_board)
    checkboard(rot90(passing_board))
    checkboard(rot180(passing_board))
    checkboard(rot270(passing_board))
