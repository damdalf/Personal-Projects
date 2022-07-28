# Finance Parser
This is a basic webscraper written in Python (using requests and 
BeautifulSoup4) which parses a list of stocks' corresponding Yahoo Finance 
pages and collects and calculates a series of statistics about the stock. 
While I hope to later add more features, such as keeping information about 
stocks over varying time intervals, comparing stocks, easily adding new stocks 
to be tracked, and many more features, this will be a project that takes some 
time.

## Implementation Details
As stated, this application is being created using Python 3.9.12, Pip3 22.0.4, 
pyenv 2.2.5, and BeautifulSoup 4.11.1.

Currently I can access a Yahoo Finance webpage and retrieve the current market 
price of a stock. I believe that it would be best to begin by creating a Stock 
class and populating it with the approriate members and methods. I will have 
to go through Hagan's information to find all of the necessary information.

* Stock
	- name
		* https://finance.yahoo.com/quote/ticker/
	- ticker
		* https://finance.yahoo.com/quote/ticker/
	- sector
		* https://finance.yahoo.com/quote/ticker/profile
	- industry
		* https://finance.yahoo.com/quote/ticker//profile
	- currentMarketPrice
		* https://finance.yahoo.com/quote/ticker/
	- atCloseDailyChange
		* https://finance.yahoo.com/quote/ticker/
	- afterHoursDailyChange
		* https://finance.yahoo.com/quote/ticker/
	- enterpriseValue
		* The company's market capitalization (number of shares 
outstanding times the current stock price), plus debt, any minority interest, 
and preferred shares, less cash and cash equivalents.
		* https://finance.yahoo.com/quote/ticker/key-statistics
	- ebit
		* The company's earnings after operating expenses (expenses 
incurred to generate the company's revenue), including misc. income and 
expenses, before payment of interest and taxes.
		* https://finance.yahoo.com/quote/ticker/financials
	- returnOnEnterpriseValue
		* This is the return on your investment, assuming you 
purchased 100% of the company.
		* formula: EBIT / Enterprise Value
		* the higher the return the better
		* a superior analysis of a company's historical performance 
and future prospect.
	- pastYearRevenue
	- YearRevenueThreeYearsAgo
	- changeInRevenuePastThreeYears
		* formula: (pastYearRevenue - revenueThreeYearsAgo) / 
revenueThreeYearsAgo * 100%
		* Growth in revenue is a good indicator of the competitive 
health of a company, if the increasing sales are from the sale of company 
products and not by acquisition. Growth by acquisition should be further 
investigated.
	- ebitMargin
		* The percentage of revenue after repayment of all costs to 
generate the revenue, including misc. income and expenses, before repayment of 
interest and taxes.
		* The greater the margin the better. This is a good indicator 
of management effectiveness; the best companies have greater margins than 
their competitors.
		* formula: (total sales - cost of goods sold - operating 
expenses) / total sales * 100%
		* not directly found on Yahoo

Once the class and it's member/methods have been created, it would be best to 
test this out on five different stocks, and once that is working, look to add 
functions that would increase the utility of the application.

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
