####################################################################################
# AUTHOR: # Devin Amdahl          # FILE: # stock.py                               #
# EMAIL:  # devinamdahl@gmail.com ##################################################
# DATE:   # 07/28/2022            # Class that represents a stock with the         #
################################### approriate members and methods for Hagan.      #
####################################################################################

from hashlib import new
from bs4 import BeautifulSoup
import requests
import datetime
from urllib.error import HTTPError, URLError

headers = { 
    'User-Agent'      : 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36', 
    'Accept'          : 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8', 
    'Accept-Language' : 'en-US,en;q=0.5',
    'DNT'             : '1', # Do Not Track Request Header 
    'Connection'      : 'close'
}

# TODO, Evaluate if it is worth it to make members private and add getters and retrieveters for the class... Python things.
class Stock:
    # Constructor.
    def __init__(self, ticker):
        # Initialize URL, webpage, and main_page.
        self.url = "https://finance.yahoo.com/quote/" + str(ticker) + "/"
        try:
            self.webpage = requests.get(self.url, headers = headers)
            self.webpage.raise_for_status()
        except HTTPError as hp:
            print("The server could not be found (HTTPError)!")
        except URLError as ue:
            print("The server could not be found (URLError)!")
        else:
            system_time = datetime.datetime.now()
            self.date_of_scrape = system_time.strftime("%Y/%m/%d")
            self.main_page = BeautifulSoup(self.webpage.content, 'html.parser')
            title = self.main_page.find('title')
            print("Connection to " + title.string + " was successful!")

        # Initialize profile_page, financials_page, and statistics_page.
        self.webpage = requests.get(self.url + "profile", headers = headers)
        self.profile_page = BeautifulSoup(self.webpage.content, 'html.parser')
        self.webpage = requests.get(self.url + "financials", headers = headers)
        self.financials_page = BeautifulSoup(self.webpage.content, 'html.parser')
        self.webpage = requests.get(self.url + "key-statistics", headers = headers)
        self.statistics_page = BeautifulSoup(self.webpage.content, 'html.parser')

        # Initialize class members.
        self.ticker = ticker;
        self.name = self.retrieveName()
        self.sector = self.retrieveSector()
        self.industry = self.retrieveIndustry()
        self.market_price = self.retrieveMarketPrice()
        # TODO add a 'at_close_daily_change', 'after_hours_daily_change', and 'dividends' members
        self.enterprise_value = self.retrieveEnterpriseValue()
        self.ebit = self.retrieveEBIT()
        self.return_on_enterprise = self.calculateReturnOnEnterpriseValue()
        self.past_year_revenue = self.retrievePastYearRevenue()
        self.revenue_three_years_ago = self.retrieveRevenueThreeYearsAgo()
        self.change_in_revenue_three_years = self.calculateChangeInRevenuePastThreeYears()
        self.ebit_margin = self.calculateEbitMargin()

    # Define class methods.
    def retrieveName(self):
        unformatted_name = self.main_page.body.find('h1')
        unformatted_name = unformatted_name
        words = unformatted_name.string.split(" ")
        name = ""

        for i in words:
            if i[0] == "(":
                break
            else:
                name += i + " "

        return name.strip()

####################################################################################

    def retrieveSector(self):
        found = 0;
        span_tags = self.profile_page.body.find_all('span')
        sector = ""

        # TODO, Look into ways of optimizing this. Ex) count # of spans before this, and skip these when searching.
        for tags in span_tags:
            if (found == 1):
                sector = tags.string
                return sector.strip()
            if tags.string == "Sector(s)":
                found = 1
        print("ERROR: Unable to find " + self.name + "'s sector!")

        return "ERROR"

####################################################################################

    def retrieveIndustry(self):
        found = 0;
        span_tags = self.profile_page.body.find_all('span')
        industry = ""

        # TODO, Look into ways of optimizing this. Ex) count # of spans before this, and skip these when searching.
        for tags in span_tags:
            if (found == 1):
                industry = tags.string
                return industry.strip()
            if tags.string == "Industry":
                found = 1
        print("ERROR: Unable to find " + self.name + "'s industry!")

        return "ERROR"
        

####################################################################################

    def retrieveMarketPrice(self):
        fin_tags = self.main_page.body.find_all('fin-streamer')
        market_price = ""

        # TODO, Look into ways of optimizing this. Ex) count # of fin-streamers before this, and skip these when searching.
        for fins in fin_tags:
            if ((fins["data-field"] == "regularMarketPrice") & (fins["data-symbol"] == self.ticker)):
                market_price = fins["value"]
                return market_price.strip()
        print("ERROR: Unable to find " + self.name + "'s current market price!")

        return "ERROR"

####################################################################################

    def retrieveEnterpriseValue(self):
        span_tags = self.statistics_page.body.find_all('span')
        enterprise_value = ""

        # TODO, Ensure that this is always retrieving the correct enterprise value for the date.
        # TODO, Look into ways of optimizing this. Ex) count # of spans before this, and skip these when searching.
        for spans in span_tags:
            if (spans.string == "Enterprise Value"):
                table_data_tags = spans.parent.parent.find_all("td")
                i = 0
                for data in table_data_tags:
                    i += 1
                    if (i == 2):
                        enterprise_value = data.string
                        return enterprise_value.strip()
        print("ERROR: Unable to find " + self.name + "'s enterprise value!")

        return "ERROR"

####################################################################################

    # TODO, Restructure to check for the unit being used for the 'financials' information. Always displayed.
    def retrieveEBIT(self):
        div_tags = self.financials_page.body.find_all('div')
        found = 0
        ebit = ""

        # TODO, Ensure that this is always retrieving the correct EBIT for the date.
        # TODO, Look into ways of optimizing this. Ex) count # of divs before this, and skip these when searching.
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
                return new_ebit.strip() + 'B'
            if (found == 2):
                found = 1
                continue
            if (divs.string == "EBIT"):
                found = 2
        print("ERROR: Unable to find " + self.name + "'s EBIT!")

        return "ERROR"

####################################################################################

    def calculateReturnOnEnterpriseValue(self):
        ebit = self.ebit.replace('B', '')
        enterprise_value = self.enterprise_value.replace(',', '')
        enterprise_value = enterprise_value.replace('B', '')
        
        # TODO, Decide if should increase precision.
        return round(float(ebit) / float(enterprise_value) * 100, 2)

####################################################################################

    # TODO, Currently retrieves YTD revenue. Change to retrieve past year's information.
    # TODO, Add checking the current date of the system - future oriented.
    # TODO, Restructure to check for the unit being used for the 'financials' information. Always displayed.
    def retrievePastYearRevenue(self):
        span_tags = self.financials_page.body.find_all('span')
        found = 0;
        past_year_revenue = ""

        # TODO, Look into ways of optimizing this. Ex) count # of spans before this, and skip these when searching.
        for spans in span_tags:
            if (found == 1):
                past_year_revenue = spans.string
                temp = ""
                floats = past_year_revenue.split(',')
                i = 0

                for f in floats:
                    if (i > 1):
                        break
                    if (i > 0):
                        temp += '.'
                    temp += str(f)
                    i += 1
                    
                return temp.strip() + 'B'

            if (spans.string == "Total Revenue"):
                found = 1
        print("ERROR: Unable to find " + self.name + "'s revenue from the past year!")

        return "ERROR"

        

####################################################################################

    # TODO, Restructure to check for the unit being used for the 'financials' information. Always displayed.
    def retrieveRevenueThreeYearsAgo(self):
        span_tags = self.financials_page.body.find_all('span')
        found = 0;
        revenue_three_years_ago = ""
        i = 0

        # TODO, Look into ways of optimizing this. Ex) count # of spans before this, and skip these when searching.
        for spans in span_tags:
            if (spans.string == "Total Revenue"):
                found = 1
                continue
            if (found == 1):
                i += 1
            if ((found == 1) & (i == 4)):
                revenue_three_years_ago = spans.string
                temp = ""
                floats = revenue_three_years_ago.split(',')
                j = 0

                for f in floats:
                    if (j > 1):
                        return temp.strip() + 'B'
                    if (j > 0):
                        temp += '.'
                    temp += str(f)
                    j += 1
        print("ERROR: Unable to find " + self.name + "'s revenue from three years ago!")

        return "ERROR"


####################################################################################

    def calculateChangeInRevenuePastThreeYears(self):
        past_year_revenue = self.past_year_revenue.replace('B', '')
        revenue_three_years_ago = self.revenue_three_years_ago.replace('B', '')

        # TODO, Decide if should increase precision.
        return round(((((float(past_year_revenue) / float(revenue_three_years_ago)) - 1) / 3) * 100), 2)
            
#################################################################################### 

    def calculateEbitMargin(self):
        past_year_revenue = self.past_year_revenue.replace('B', '')
        ebit = self.ebit.replace('B', '')

        # TODO, Decide if should increase precision.
        return round((float(ebit) / float(past_year_revenue) * 100), 2) 

####################################################################################

    def printName(self):
        print("NAME:")
        print(str(self.name) + "\n")

####################################################################################

    def printSector(self):
        print("SECTOR:")
        print(str(self.sector) + "\n")

####################################################################################

    def printIndustry(self):
        print("INDUSTRY:")
        print(str(self.industry) + "\n")

####################################################################################

    def printMarketPrice(self):
        print("MARKET PRICE:")
        print("$" + str(self.market_price) + "\n")

####################################################################################

    def printEnterpriseValue(self):
        print("ENTERPRISE VALUE:")
        print("$" + str(self.enterprise_value) + "\n")

####################################################################################

    def printEBIT(self):
        print("EBIT:")
        print("$" + str(self.ebit) + "\n")

####################################################################################

    def printReturnOnEnterpriseValue(self):
        print("RETURN ON ENTERPRISE VALUE:")
        print(str(self.return_on_enterprise) + "%\n")

####################################################################################

    def printPastYearRevenue(self):
        print("PAST YEAR'S REVENUE:")
        print("$" + str(self.past_year_revenue) + "\n")

####################################################################################

    def printRevenueFromThreeYearsAgo(self):
        print("REVENUE THREE YEARS AGO:")
        print("$" + str(self.revenue_three_years_ago) + "\n")

####################################################################################

    def printChangeInRevenueLastThreeYears(self):
        print("CHANGE IN REVENUE LAST THREE YEARS:")
        print(str(self.change_in_revenue_three_years) + "%\n")

####################################################################################

    def printEbitMargin(self):
        print("EBIT MARGIN:")
        print(str(self.ebit_margin) + "%\n")

####################################################################################

    def printDateOfLog(self):
        print("Date of scrape: " + self.date_of_scrape)

####################################################################################

    # TODO, Abstract some of this - indidivual print methods for groupings.
    def printBasicInfo(self):
        print('=============================================================================')
        self.printDateOfLog()
        print('=============================================================================\n')
        self.printName()
        self.printSector()
        self.printIndustry()
        self.printMarketPrice()
        self.printEnterpriseValue()
        self.printReturnOnEnterpriseValue()
        self.printRevenueFromThreeYearsAgo()
        self.printEbitMargin()
        print('=============================================================================')
        print('#############################################################################')
        print('=============================================================================\n')

####################################################################################