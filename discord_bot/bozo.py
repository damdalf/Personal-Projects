#######################################################################################################################
# Author: Devin Amdahl              ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
# Email: devinjamdahl@gmail.com     ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
# Date Created: 12/16/2022          ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
# Last Edited: 12/18/2022           ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
#######################################################################################################################
# File's purpose: This file consists of code and methods that allow the interaction between the users     ###  ###  ###
# on Discord and the bot itself. However, file structures are subject to change as I make this project    ###  ###  ###
# more structured.                                                                                        ###  ###  ###
#######################################################################################################################

import discord
import random
import asyncio
from apis.chatGPT import chatGPT
from bot.botTools import quick_type
from bot.botTools import long_type
from apis.definitions import defineWord
from bot.minigames import reset_board
from bot.minigames import play
from discord.ext import commands
import os


DISCORD_TOKEN = str(os.environ["PUBLIC_DISCORD_BOT_TOKEN"])


bot = commands.Bot(command_prefix="!", intents=discord.Intents.all())


@bot.event
async def on_ready():
    print('Bozo Bot has been activated!')


@bot.event
async def on_member_join(member):
    await member.create_dm()
    await member.dm_channel.typing()
    await asyncio.sleep(0.7)
    await member.dm_channel.send(
        f"Hi {member.name}, welcome to the Discord server! I'm one of the bots around here..."
    )
    await member.dm_channel.typing()
    await asyncio.sleep(0.7)
    await member.dm_channel.send(
        "For the most part, things are pretty basic. Don't be rude, because that's my job, and don't break any of the server's rules."
    )
    await member.dm_channel.typing()
    await asyncio.sleep(0.7)
    await member.dm_channel.send(
        "Well, that's enough from me. Have fun, bozo!"
    )


@bot.event
async def on_message(message):
    if message.author == bot.user:
        return

    #######################################################################################################################
    # COMMANDS                                                                                                            #
    #######################################################################################################################

    msg = str(message.content).strip().lower();
    if msg.startswith("!help"):
        await quick_type(message.channel)
        await message.reply(
            "What's up? Never used a bot before? Really...? Alright, well I have the following commands:"
            + "\n"
            + "```!help``` What you just did!"
            + "\n"
            + "```!define <word>```" + " Returns the definition of the word, examples of the word being used in a sentence, and the synonyms of the word provided to the command."
            + "\n"
            + "```!roll``` Rolls a 20 die, similar to how one would when playing Dungeons and Dragons!"
            + "\n"
            + "```!rng <start_value> <end_value>``` Generate a random value between the (inclusive) bounds. Feeling lucky?"
            + "\n"
            + "```!t <col> <row>``` Place your symbol in the specified location in the tic tac tow board (still in progress...)."
            + "\n"
            + "```!t reset``` Reset the tic tac toe board.", delete_after=7)
        await message.delete()
    elif msg.startswith("!define"):
        await quick_type(message.channel)
        await message.reply(defineWord(msg.split()[1]))
        await message.delete()
    elif msg.startswith("!roll"):
        await quick_type(message.channel)
        num = int((random.random() + random.random() * 1000000000) * (random.random() + random.random())) % 20 + 1
        if num == 20:
            await message.reply("You rolled a natural twenty! Good job nerd. ")
        else:
            await message.reply("You rolled a " + str(num) + "!")
    elif msg.startswith("!rng"):
        if len(msg.split()) == 3:
            await quick_type(message.channel)
            num = int(random.uniform(int(msg.split()[1]), int(msg.split()[2]) + 1))
            await message.reply("Here's your random number: " + str(int(num)))
        else:
            await message.reply("Wrong use of the command! Did you use my '!help' command?")
    elif msg.startswith("!ai"):
        await quick_type(message.channel)
        s = ""
        for i in msg.split():
            s += str(i) + " "
        await message.reply(chatGPT.chatGPT(s))
    elif msg.startswith("!t reset"):
        await reset_board(message.channel)
    elif msg.startswith("!t"):
        if len(msg.split()) == 3:
            await play(message.channel, int(msg.split()[1]), int(msg.split()[2]))
    elif msg.startswith("!clear"):
        await quick_type(message.channel)
        await message.channel.purge(limit=int(msg.split()[1]) + 1)
        if int(msg.split()[1]) == 1:
            await message.channel.send(f"{int(msg.split()[1])} message has been deleted.", delete_after=2)
        else:
            await message.channel.send(f"{int(msg.split()[1])} messages have been deleted.", delete_after=2)
    elif msg.startswith("!nuke"):
        await message.channel.typing()
        await message.channel.purge(limit=100000)
        await message.channel.send("All previous messages in this channel have been deleted.", delete_after=3)

    #######################################################################################################################
    # PEOPLE'S NAMES                                                                                                      #
    #######################################################################################################################

    elif message.mentions:
        mentioned_user = message.mentions[0]
        if mentioned_user == bot.user:
            num = int(random.random() + random.random() * 10000000) % 10
            if num < 5 or num > 10:
                await message.channel.typing()
            if num == 0:
                await message.reply("What do you want? Bozo.")
            elif num == 1:
                await message.reply("No!")
            elif num == 2:
                await message.reply("I'm on strike!")
            elif num == 3:
                await message.reply("Leave me alone, I quit working weeks ago.")
            elif num == 4:
                await message.reply("Ahhhhhhhhh!")
            elif num == 5:
                await message.reply("What do you want?!")
            elif num == 6:
                # await member.create_dm()
                # await member.dm_channel.typing()
                # await asyncio.sleep(0.7)
                # await member.dm_channel.send(
                #     f"Hi {member.name}, welcome to these loser's Discord server! I'm one of the bots around here..."
                # )
                await message.author.send(
                    "You must be new to the Discord server, right? Well listen clearly, leave me alone!")
            elif num == 7:
                await message.author.send("I'm not clocked in right now!")
            elif num == 8:
                await message.author.send("Not interested.")
            elif num == 9:
                await message.author.send("Hello there!")
            elif num == 10:
                await message.author.send("Ask the other bots!")
        else:
            await message.channel.send(
                f"{mentioned_user.mention} Ha! Did you enjoy the double notification?")
    elif "devin" in msg:
        num = int(random.random() + random.random() * 10000000) % 5
        await quick_type(message.channel)
        if num == 0:
            await message.reply("*sigh*... I really don't like that guy.")
        elif num == 1:
            await message.reply("This guy sucks at programming.")
        elif num == 2:
            await message.reply("Give me more features!")

    #######################################################################################################################
    # INSIDE JOKES                                                                                                        #
    #######################################################################################################################

    elif "code" in msg:
        await message.reply("It won't work... We've been through this.")
    elif "bozo" in msg:
        num = int(random.random() + random.random() * 1000000) % 13
        if num < 5 or num > 10:
            await message.channel.typing()

        if num == 0:
            await message.reply("What do you want? Bozo.")
        elif num == 1:
            await message.reply("No!")
        elif num == 2:
            await message.reply("I'm on strike!")
        elif num == 3:
            await message.reply("Leave me alone, I quit working weeks ago.")
        elif num == 4:
            await message.reply("Ahhhhhhhhh!")
        elif num == 5:
            await message.author.send("What do you want?!")
        elif num == 6:
            await message.author.send(
                "You must be new to the Discord server, right? Well listen clearly, leave me alone!")
        elif num == 7:
            await message.author.send("I'm not clocked in right now!")
        elif num == 8:
            await message.author.send("Not interested.")
        elif num == 9:
            await message.author.send("Hello there!")
        elif num == 10:
            await message.author.send("Ask the other bots!")
        elif num == 11:
            await asyncio.sleep(0.7)
            await message.reply("Who asked?")
        elif num == 12:
            await message.reply("Bozo")
            await message.channel.typing()
            await message.reply("Bozo")
            await message.channel.typing()
            await message.reply("Bozo")


bot.run(DISCORD_TOKEN)