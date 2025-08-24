import tkinter as tk
from tkinter import messagebox
import math

AI = "X"
HUMAN = "O"
EMPTY = "."

# --- Game logic ---
def winner(board):
    lines = [
        (0,1,2), (3,4,5), (6,7,8),  # rows
        (0,3,6), (1,4,7), (2,5,8),  # cols
        (0,4,8), (2,4,6)            # diagonals
    ]
    for a, b, c in lines:
        if board[a] != EMPTY and board[a] == board[b] == board[c]:
            return +1 if board[a] == AI else -1
    if EMPTY not in board:
        return 0  # draw
    return None   # game continues

def minimax(board, is_ai_turn):
    state = winner(board)
    if state is not None:
        return state
    if is_ai_turn:
        best = -math.inf
        for i in range(9):
            if board[i] == EMPTY:
                board[i] = AI
                score = minimax(board, False)
                board[i] = EMPTY
                best = max(best, score)
        return best
    else:
        best = math.inf
        for i in range(9):
            if board[i] == EMPTY:
                board[i] = HUMAN
                score = minimax(board, True)
                board[i] = EMPTY
                best = min(best, score)
        return best

def best_move(board):
    best_val = -math.inf
    move = -1
    for i in range(9):
        if board[i] == EMPTY:
            board[i] = AI
            score = minimax(board, False)
            board[i] = EMPTY
            if score > best_val:
                best_val = score
                move = i
    return move

# --- GUI ---
class TicTacToe:
    def __init__(self, root):
        self.root = root
        self.root.title("Tic Tac Toe - Unbeatable AI")
        self.board = [EMPTY] * 9
        self.buttons = []

        for i in range(9):
            btn = tk.Button(root, text=" ", font=("Arial", 20), width=5, height=2,
                            command=lambda i=i: self.human_move(i))
            btn.grid(row=i//3, column=i%3)
            self.buttons.append(btn)

    def human_move(self, i):
        if self.board[i] == EMPTY and winner(self.board) is None:
            self.board[i] = HUMAN
            self.buttons[i].config(text=HUMAN, state="disabled")
            if winner(self.board) is None:
                self.ai_move()
            else:
                self.end_game()

    def ai_move(self):
        move = best_move(self.board)
        if move != -1:
            self.board[move] = AI
            self.buttons[move].config(text=AI, state="disabled")
        if winner(self.board) is not None:
            self.end_game()

    def end_game(self):
        result = winner(self.board)
        if result == +1:
            messagebox.showinfo("Game Over", "AI wins 😎")
        elif result == -1:
            messagebox.showinfo("Game Over", "You win! 🎉 (rare, unless AI bug!)")
        else:
            messagebox.showinfo("Game Over", "It's a draw 🤝")
        self.reset()

    def reset(self):
        self.board = [EMPTY] * 9
        for btn in self.buttons:
            btn.config(text=" ", state="normal")

# --- Run the game ---
if __name__ == "__main__":
    root = tk.Tk()
    game = TicTacToe(root)
    root.mainloop()
