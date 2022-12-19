#######################################################################################################################
# Author: Devin Amdahl              ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
# Email: devinjamdahl@gmail.com     ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
# Date Created: 12/16/2022          ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
# Last Edited: 12/18/2022           ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
#######################################################################################################################
# File's purpose: This file consists of code and methods that allow the user to query the Words API to    ###  ###  ###
# retrieve the definition (and some other information, this will eventually be expanded) of a word.       ###  ###  ###
#######################################################################################################################
import os
import requests

API_KEY = os.environ["WORDS_API_KEY"]

urlStart = "https://wordsapiv1.p.rapidapi.com/words/"
urlEndDefinition = "/definitions"
urlEndExamples = "/examples"
urlEndSynonyms = "/synonyms"

headers = {
    "X-RapidAPI-Key": API_KEY,
    "X-RapidAPI-Host": "wordsapiv1.p.rapidapi.com"
}


def failure():
    return "**Definition: a person with a record of failing; someone who loses consistently**\n**Part of speech:** noun"


def defineWord(word):
    # Get definition and part of speech.
    response = requests.request("GET", urlStart + word + urlEndDefinition, headers=headers)
    data = response.json()
    if response.status_code != 200:
        return failure()
    definition = ("**Definition: **" + str(data["definitions"][0]["definition"]))
    partOfSpeech = ("**Part of speech: **" + str(data["definitions"][0]["partOfSpeech"]))

    # Get the list of examples of the word being used in a sentence.
    response = requests.request("GET", urlStart + word + urlEndExamples, headers=headers)
    data = response.json()
    if response.status_code != 200:
        return failure()
    examples = ""
    count = 0
    for i in data["examples"]:
        count += 1
        examples += "**Example " + str(count) + ": **" + str(i) + "\n"
        if count >= 3:
            break

    # Get the list of the word's synonyms.
    response = requests.request("GET", urlStart + word + urlEndSynonyms, headers=headers)
    data = response.json()
    if response.status_code != 200:
        return failure()
    synnonyms = ""
    count = 0
    for i in data["synonyms"]:
        count += 1
        synnonyms += "**Synonym " + str(count) + ": **" + str(i) + "\n"
        if count >= 3:
            break

    return definition + "\n" + partOfSpeech + "\n\n" + examples + "\n" + synnonyms