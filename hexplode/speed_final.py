from hexplode import algo_player
import time

'''
Mihail Dunaev
The University of Edinburgh
mihail.dunaev91@gmail.com
10 Jan 2016

Bot for hexplode challenge.
Speed bot
  Uses alpha-beta (with pruning) with mediocre heuristics.
  It tries to go as deep as possible.
'''

MAX_TURN_TIME = 4.9
depth = 5
start_time = 0
neigh = {}

@algo_player(name="speed",
             description="In speed we trust \m/")
def speed(board, game_id, player_id):

    global start_time, depth
    start_time = time.time()

    (np,ne) = init(board, player_id, 1 - player_id)

    lazy_board = {}
    (val, key) = best_move(board, lazy_board, player_id, np, ne, depth, 2)
    return key

# alpha-beta with pruning
def best_move(board, lazy_board, player_id, np, ne, depth, pbv):

    global start_time, neigh
    delta_time = time.time() - start_time

    # best value, best key
    bv = -2
    bk = None
    enemy_id = 1 - player_id

    # find all possible moves
    possible_states = []
    append = possible_states.append
    for key in board:
        empty = True
        if key in lazy_board:
            if lazy_board[key]['player'] == enemy_id:
                continue
            if lazy_board[key]['player'] == player_id:
                empty = False
        else:
            if board[key]['player'] == enemy_id:
                continue
            if board[key]['player'] == player_id:
                empty = False

        # (hard) copy the lazy board
        tmp_board = {}
        for k in lazy_board:
            tmp_board[k] = lazy_board[k].copy()

        # add key to new lazy board
        if key not in tmp_board:
            tmp_board[key] = {'player':board[key]['player'], 'counters':board[key]['counters']}

        # compute the gain for the key
        gain = 0
        phd = neigh[key] - tmp_board[key]['counters']
        stop = False
        for nk in board[key]['neighbours']:
            if nk in tmp_board:
                if tmp_board[nk]['player'] == (1 - player_id):
                    ehd = neigh[nk] - tmp_board[nk]['counters']
                    if ehd < phd:
                        gain = -(tmp_board[key]['counters']/ehd)
                        stop = True
                        break
                    else:
                        gain = gain + tmp_board[nk]['counters']
            else:
                if board[nk]['player'] == (1 - player_id):
                    ehd = neigh[nk] - board[nk]['counters']
                    if ehd < phd:
                        gain = -(board[key]['counters']/ehd)
                        stop = True
                        break
                    else:
                        gain = gain + board[nk]['counters']
        if stop == False:
            gain = gain/phd

        # simulate the move, if it's winning move, return
        (ret, new_np, new_ne) = make_move(board, tmp_board, key, player_id, np, ne)
        if ret == True:
            return (1,key)

        # compute hex distance (to hexplode)
        hd = neigh[key] - tmp_board[key]['counters']
        if empty == False:
            hd = hd + 11

        # compute the new eval
        total = new_np + new_ne
        evl = 0
        if total != 0:
            evl = (new_np - new_ne) / (new_np + new_ne)
        append((key,tmp_board,hd,-evl,new_np,new_ne,-gain))

    # sort new states, fist after eval, second after gain and third after hd
    sorted_states = sorted(possible_states,key=lambda x:(x[3],x[6],x[2]))

    # take them in order, return best move
    for elem in sorted_states:
        key = elem[0]
        val = 0
        if depth > 1 and delta_time < MAX_TURN_TIME:
            (val, tk) = best_move(board, elem[1], enemy_id, elem[5], elem[4], depth - 1, -bv)
            val = -val
            if val == 1:
                return (1,key)
            if val >= pbv:
                return (val,key)
        else:
            val = -elem[3]
            if depth == 1:
                return (val,key)
        if bv < val:
            bv = val
            bk = key
    return (bv,bk)

# makes one move on key & simulates explosion
def make_move(board, lazy_board, key, player_id, np, ne):

    global neigh
    new_np = np
    new_ne = ne
    keys = [key]
    count = 1
    pop = keys.pop
    append = keys.append
    while count > 0:
        k = pop()
        count = count - 1

        lazy_board[k]['counters'] = lazy_board[k]['counters'] + 1
        if lazy_board[k]['counters'] <= 0:
            continue

        new_np = new_np + 1
        if lazy_board[k]['counters'] == 1:
            lazy_board[k]['player'] = player_id
            continue

        # increment and check for explosions
        #lazy_board[k]['counters'] = lazy_board[k]['counters'] + 1
        nn = neigh[k]
        if lazy_board[k]['counters'] >= nn:
            lazy_board[k]['counters'] = lazy_board[k]['counters'] - nn
            new_np = new_np - nn
            if lazy_board[k]['counters'] == 0:
                lazy_board[k]['player'] = None
            for nk in board[k]['neighbours']:
                if nk not in lazy_board:
                    lazy_board[nk] = {'player':board[nk]['player'], 'counters':board[nk]['counters']}
                if lazy_board[nk]['player'] == (1 - player_id):
                    lazy_board[nk]['player'] = player_id
                    new_np = new_np + lazy_board[nk]['counters']
                    new_ne = new_ne - lazy_board[nk]['counters']
                    if new_ne <= 0:
                        return (True, new_np, new_ne)
                append(nk)
                count = count + 1
    return (False, new_np, new_ne)

# counts player & enemy score, neigh & counters init
def init(board, player_id, enemy_id):
    global neigh
    np = ne = 0
    for key in board:
        neigh[key] = len(board[key]['neighbours'])
        if board[key]['player'] == enemy_id:
            ne = ne + board[key]['counters']
        elif board[key]['player'] == player_id:
            np = np + board[key]['counters']
        elif board[key]['counters'] is None:
            board[key]['counters'] = 0
    return (np,ne)

@speed.on_start_game
def start_game(game_id, player_id, boardsize, opponent_id):
    global depth
    if boardsize == 3:
        depth = 7
        return
    if boardsize == 4:
        depth = 5
        return
    if boardsize == 5:
        depth = 5
        return
    if boardsize == 6:
        depth = 4
        return
    depth = 3
