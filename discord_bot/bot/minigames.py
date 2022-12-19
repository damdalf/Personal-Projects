#######################################################################################################################
# Author: Devin Amdahl              ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
# Email: devinjamdahl@gmail.com     ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
# Date Created: 12/16/2022          ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
# Last Edited: 12/18/2022           ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
#######################################################################################################################
# File's purpose: This file consists of code and methods that allow the Discord user's to play            ###  ###  ###
# text-based games through the servers channel. However, file structure is subject to change as I make    ###  ###  ###
# this project more structured.                                                                           ###  ###  ###
#######################################################################################################################

import discord
import asyncio
import random
from discord.ext import commands

bot = commands.Bot(command_prefix='!', intents=discord.Intents.all())
moves_made = 0
board = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
current_player = random.random() + 1 % 2


async def initalize_board():
    global moves_made
    global board
    global current_player
    moves_made = 0
    board = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
    current_player = random.random() + 1 % 2


async def reset_board(ctx):
    global moves_made
    global board
    global current_player
    board = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
    for row in range(len(board)):
        for col in range(len(board[row])):
            board[row][col] = 0
    global moves_made
    moves_made = 0
    await ctx.typing()
    await asyncio.sleep(0.7)
    await ctx.send("Resetting the board...")


async def is_draw():
    global moves_made
    global board
    global current_player
    for row in range(len(board)):
        for col in range(len(board[row])):
            if board[row][col] == 0:
                return False
    return True


def format_board():
    global board
    board_str = "-----------\n"
    for row in range(len(board)):
        for col in range(len(board[row])):
            if board[row][col] == 1:
                board_str += "| X "
            elif board[row][col] == 2:
                board_str += "| O "
            else:
                board_str += "|     "
        board_str += "|\n"
        board_str += "-----------\n"
    return board_str


async def check_winner(ctx):
    global moves_made
    global board
    global current_player
    true = False
    for row in range(3):
        if board[row][0] == board[row][1] == board[row][2] and board[row][0] != 0:
            true = True

    for col in range(3):
        if board[0][col] == board[1][col] == board[2][col] and board[0][col] != 0:
            true = True

    if board[0][0] == board[1][1] == board[2][2] and board[0][0] != 0:
        true = True
    if board[0][2] == board[1][1] == board[2][0] and board[0][2] != 0:
        true = True

    if true:
        if current_player == 1:
            await ctx.send("Player 'X' wins!")
        else:
            await ctx.send("Player 'O' wins!")
        await reset_board(ctx)


async def play(ctx, row: int, col: int):
    global moves_made
    global board
    global current_player

    if board[row][col] == 0:
        moves_made += 1
        current_player = moves_made % 2 + 1
    else:
        await ctx.send("Sorry, that position has already been taken! Try again.")

    board[row][col] = current_player
    await ctx.send(format_board())
    if await check_winner(ctx):
        return
    if moves_made == 9 and is_draw():
        await ctx.send("It's a draw!")
        await reset_board(ctx)
        return
