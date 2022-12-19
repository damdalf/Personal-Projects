#######################################################################################################################
# Author: Devin Amdahl              ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
# Email: devinjamdahl@gmail.com     ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
# Date Created: 12/16/2022          ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
# Last Edited: 12/18/2022           ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
#######################################################################################################################
# File's purpose: This file consists of code and methods that allow the user to query the ChatGPT AI from ###  ###  ###
# OpenAI. This is done through OpenAI's ChatGPT API.                                                      ###  ###  ###
#######################################################################################################################

import requests
import os

API_KEY = os.environ["CHAT_GPT_API_KEY"]

def chatGPT(text):
    url = "https://api.openai.com/v1/completions"
    headers = {
        "Content-Type": "application/json",
        "Authorization": "Bearer " + API_KEY,
    }
    data = {
        "model": "text-davinci-003",
        "prompt": text,
        "max_tokens": 4000,
        "temperature": 1.0,
    }
    response = requests.post(url, headers=headers, json=data)
    if response.status_code == 200:
        output = response.json()["choices"][0]["text"]
        return str(output)