####################################################################################
# AUTHOR: # Devin Amdahl          # FILE: # general tests.py                       #
# EMAIL:  # devinamdahl@gmail.com ##################################################
# DATE:   # 07/28/2022            # Class that represents a stock with the         #
################################### approriate members and methods for Hagan.      #
####################################################################################

# TODO, Evaluate if it is worth it to make members private and add getters and retrieveters for the class... Python things.

from hashlib import new
from bs4 import BeautifulSoup
import requests

headers = { 
    'User-Agent'      : 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36', 
    'Accept'          : 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8', 
    'Accept-Language' : 'en-US,en;q=0.5',
    'DNT'             : '1', # Do Not Track Request Header 
    'Connection'      : 'close'
}

class Stock:
    # Constructor.
    def __init__(self, ticker):
        # Initialize URL, webpage, and main_page.
        self.url = "https://finance.yahoo.com/quote/" + str(ticker) + "/"
        self.webpage = requests.get(self.url, headers = headers)
        self.main_page = BeautifulSoup(self.webpage.content, 'html.parser')
        # Initialize profile_page.
        self.webpage = requests.get(self.url + "profile", headers = headers)
        self.profile_page = BeautifulSoup(self.webpage.content, 'html.parser')
        # Initialize financials_page.
        self.webpage = requests.get(self.url + "financials", headers = headers)
        self.financials_page = BeautifulSoup(self.webpage.content, 'html.parser')
        # Initialize statistics_page.
        self.webpage = requests.get(self.url + "key-statistics", headers = headers)
        self.statistics_page = BeautifulSoup(self.webpage.content, 'html.parser')

        # Initialize class members.
        self.ticker = ticker;
        self.name = self.retrieveName()
        self.sector = self.retrieveSector()
        self.industry = self.retrieveIndustry()
        self.market_price = self.retrieveMarketPrice()
        # TODO add a 'at_close_daily_change' and 'after_hours_daily_change' members
        self.enterprise_value = self.retrieveEnterpriseValue()
        self.ebit = self.retrieveEBIT()
        self.return_on_enterprise = self.calculateReturnOnEnterpriseValue()

    # Define class methods.
    def retrieveName(self):
        unformatted_name = self.main_page.body.find_all('h1')
        unformatted_name = unformatted_name[0]
        words = unformatted_name.string.split(" ")
        name = ""

        for i in words:
            if i[0] == "(":
                break
            else:
                name += i + " "

        return name.strip()

    def retrieveSector(self):
        found = 0;
        span_tags = self.profile_page.body.find_all('span')
        sector = ""

        for tags in span_tags:
            if (found == 2):
                sector = tags.string
                break
            if tags.string == "Sector(s)":
                found = 2

        return sector.strip()

    def retrieveIndustry(self):
        found = 0;
        span_tags = self.profile_page.body.find_all('span')
        industry = ""

        for tags in span_tags:
            if (found == 1):
                industry = tags.string
                break
            if tags.string == "Industry":
                found = 1

        return industry.strip()

    def retrieveMarketPrice(self):
        fin_tags = self.main_page.body.find_all('fin-streamer')
        market_price = ""

        for fins in fin_tags:
            if ((fins["data-field"] == "regularMarketPrice") & (fins["data-symbol"] == self.ticker)):
                market_price = fins["value"]

        return market_price.strip()

    def retrieveEnterpriseValue(self):
        span_tags = self.statistics_page.body.find_all('span')
        enterprise_value = ""

        for spans in span_tags:
            if (spans.string == "Enterprise Value"):
                table_data_tags = spans.parent.parent.find_all("td")
                i = 0
                for data in table_data_tags:
                    i += 1
                    if (i == 2):
                        enterprise_value = data.string

        return enterprise_value.strip()

    def retrieveEBIT(self):
        div_tags = self.financials_page.body.find_all('div')
        found = 0
        ebit = ""

        for divs in div_tags:
            if (found == 1):
                ebit = divs.string
                i = 0
                new_ebit = ""
                floats = ebit.split(',')
                for f in floats:
                    if (i > 1):
                        break
                    if (i > 0):
                        new_ebit += '.'
                    new_ebit += str(f)
                    i += 1
                break
            if (found == 2):
                found = 1
                continue
            if (divs.string == "EBIT"):
                found = 2

        return new_ebit.strip() + 'B'

    def calculateReturnOnEnterpriseValue(self):
        ebit = self.ebit.replace('B', '')
        enterprise_value = self.enterprise_value.replace(',', '')
        enterprise_value = enterprise_value.replace('B', '')
        return round(float(ebit) / float(enterprise_value) * 100, 2)
            
