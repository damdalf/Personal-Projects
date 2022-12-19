#######################################################################################################################
# Author: Devin Amdahl              ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
# Email: devinjamdahl@gmail.com     ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
# Date Created: 12/16/2022          ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
# Last Edited: 12/18/2022           ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
#######################################################################################################################
# File's purpose: This file consists of methods whose value is tied with interaction with the Bozo Bot,   ###  ###  ###
# are considered more "utility" methods, and simply things I decided not to have directly in "bozo.py"    ###  ###  ###
# at this current point in time. Things will probably change as the projects becomes more structured.     ###  ###  ###
#######################################################################################################################

import asyncio

async def quick_type(ctx):
    await ctx.typing()
    await asyncio.sleep(0.7)


async def long_type(ctx):
    await ctx.typing()
    await asyncio.sleep(5)