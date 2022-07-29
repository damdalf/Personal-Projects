####################################################################################
# AUTHOR: # Devin Amdahl          # FILE: # stock_test.py                          #
# EMAIL:  # devinamdahl@gmail.com ##################################################
# DATE:   # 07/28/2022            # Serves as an easy file to test all of the      #
################################### methods of the Stock class.                    #
####################################################################################

# TODO, Adding actual unit tests would be a great next step.

import stock

# Test for a single stock.
# Old Runtime: 5.03 seconds
# New Runtime: 4.42 seconds
s = stock.Stock("TSN")
s.printBasicInfo()

# Test for ten stocks.
# Old Runtime: 43.90 seconds
# New Runtime: 36.24 seconds
stock_names = ["CPB", "PINS", "MELI", "SQ", "SE", "SHOP", "ISRG", "DIS", "ABBV", "MRK"]
stocks = []
i = 0
for names in stock_names:
    stocks.append(stock.Stock(names))
    stocks[i].printBasicInfo()
    i += 1