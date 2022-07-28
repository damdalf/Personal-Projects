####################################################################################
# AUTHOR: # Devin Amdahl          # FILE: # general_tests.py                       #
# EMAIL:  # devinamdahl@gmail.com ##################################################
# DATE:   # 07/28/2022            # Serves as an easy file to test different       #
################################### method implementations, and to try new things. #
####################################################################################
# Useful tutorial: https://www.youtube.com/watch?v=gRLHr664tXA

# First attempt at parsing a webpage using Python and BeautifulSoup4.

from bs4 import BeautifulSoup
import requests

# The use of a user agent helps decrease the chances of your web scraper being label as a bot by the website and being denied access.
# To really increase the chances, for situations when you are making many requests, cycle through different predefined user agents.
headers = { 
    'User-Agent'      : 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36', 
    'Accept'          : 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8', 
    'Accept-Language' : 'en-US,en;q=0.5',
    'DNT'             : '1', # Do Not Track Request Header 
    'Connection'      : 'close'
}

website = requests.get("https://finance.yahoo.com/quote/MRK/")

# Ensure that the request was successful (returns a 200 status). Any other returned status is indicating an error with the request.
print(website)
print()

# Let's now read the HTML content of the website.
soup = BeautifulSoup(website.content, 'html.parser')

# Collect all <div> elements found in the webpage's body.
div_tags = soup.body.find_all('fin-streamer')

# Search the <div> tags and look for the current market price of the stock.
for soups in div_tags:
    if ((soups["data-field"] == "regularMarketPrice") & (soups["data-symbol"] == "MRK")):
        print(soups["value"])

# Search the <h1> tags and look for the stock's sector.
h1_tags = soup.body.find_all("h1")

for soups in h1_tags:
    print(soups.string)

span_tags = soup.body.find_all('span')

found = 0;

for soups in span_tags:
    if (found == 1):
        print(soups.string)
        break
    if soups.string == "Sector(s)":
        found = 1

# Change the website being parsed to the 'statistics' page.

website = requests.get("https://finance.yahoo.com/quote/MRK/key-statistics", headers = headers)
soup = BeautifulSoup(website.content, 'html.parser')

# Search the <span> tags and look for the stock's enterprise value.

tags = soup.body.find_all('span')

for soups in tags:
    if (soups.string == "Enterprise Value"):
        print(soups.string)
        rows = soups.parent.parent.find_all("td")
        i = 0
        for soups in rows:
            i += 1
            if (i == 2):
                print(soups.string)
        found = 1