# Finance Parser
This is a basic webscraper written in Python (using requests and 
BeautifulSoup4) which parses a list of stocks' corresponding Yahoo Finance 
pages and collects and calculates a series of statistics about the stock. 
While I hope to later add more features, such as keeping information about 
stocks over varying time intervals, comparing stocks, easily adding new stocks 
to be tracked, and many more features, this will be a project that takes some 
time.

---
## Installation Steps
As stated, this application is being created using Python 3.9.12, Pip3 22.0.4, 
pyenv 2.2.5 (not neccessary), BeautifulSoup 4.11.1, and requests.

### Python
* Windows
	1. Check your current version of Python: ```C:\> python --version```
	2. If your current version is out of date, or you do not have it installed, you have the following options:
		* Installing via the Microsoft Store
		* Installing from Python's [website](https://www.python.org/)
* MacOS
	1. Check your current version of Python: ```python3 --version ```
	2. If your current version is out of date, or you do not have it installed, you have the following options:
		* Using Homebrew: ```brew install python3```
		* Installing from Python's [website](https://www.python.org/)
* Linux
	1. Check your current version of Python: ```python3 --version ```
	2. If your current version is out of date, or you do not have it installed, you have the following options:
		* Installing with your distribution's package manager
		* Installing from Python's [website](https://www.python.org/)

### Pip
Pip should be automatically installed with your Python installation. However, you can double check with the following commands:
* Windows
	* ```pip --version```
* MacOS
	* ```pip3 --version```
* Linux
	* ```pip3 --version```

### BeautifulSoup4
* Windows
	* ```pip install BeautifulSoup4```
* MacOS
	* ```pip3 install BeautifulSoup4```
* Linux
	* ```pip3 install BeautifulSoup4```

### requests
* Windows
	* ```python -m pip install requests```
* MacOS
	* ```pip3 install requests```
* Linux
	* ```pip3 install requests```

---
## Current Features
While there are still bugs with different stocks, the stock scraper can retrieve and calculate the following information about most stocks listed on Yahoo Finance:

The stock's
* name
* ticker
* sector
* industry
* currentMarketPrice
* atCloseDailyChange
* afterHoursDailyChange
* enterpriseValue
	- The company's market capitalization (number of shares 
outstanding times the current stock price), plus debt, any minority interest, 
and preferred shares, less cash and cash equivalents.
* ebit
	- The company's earnings after operating expenses (expenses 
incurred to generate the company's revenue), including misc. income and 
expenses, before payment of interest and taxes.
* returnOnEnterpriseValue
	- formula: EBIT / Enterprise Value
	- This is the return on your investment, assuming you purchased 100% of the company.
	- the higher the return the better
	- a superior analysis of a company's historical performance and future prospect.
* pastYearRevenue
* YearRevenueThreeYearsAgo
* changeInRevenuePastThreeYears
	- Growth in revenue is a good indicator of the competitive health of a company, if the increasing sales are from the sale of company products and not by acquisition. Growth by acquisition should be further investigated.
* ebitMargin
	- formula: (total sales - cost of goods sold - operating expenses) / total sales * 100%
	- The percentage of revenue after repayment of all costs to generate the revenue, including misc. income and expenses, before repayment of interest and taxes.
	- The greater the margin the better. This is a good indicator of management effectiveness; the best companies have greater margins than their competitors.

---
## Future Features
- It would be nice to store the information about a stock each day, and then 
compile monthly reports about the stock. At first, just begin with the 
information being collected each day and averaged from there. Eventually, it 
would be nice for the application to parse the stock's YTD information and 
generate the most thorough and up-to-date reports regardless of when a user 
began using the application.

- While it's nice to be able to retrieve information about a stock after 
manually editing the 
code to include a stock, it would be far more useful to others to create a 
live 'search' method which accepts a stock's symbol, and returns the stock's 
information in an organized manner. From there, a user should be prompted 
about adding the stock to their automatically searched list.  
