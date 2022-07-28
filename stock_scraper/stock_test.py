####################################################################################
# AUTHOR: # Devin Amdahl          # FILE: # stock_test.py                          #
# EMAIL:  # devinamdahl@gmail.com ##################################################
# DATE:   # 07/28/2022            # Serves as an easy file to test all of the      #
################################### methods of the Stock class.                    #
####################################################################################

# TODO, Adding actual unit tests would be a great next step.

import stock

mrk = stock.Stock("CPB")
print("NAME:")
print(mrk.name)
print()

print("SECTOR:")
print(mrk.sector)
print()

print("INDUSTRY:")
print(mrk.industry)
print()

print("MARKET PRICE:")
print(mrk.market_price)
print()

print("ENTERPRISE VALUE:")
print(mrk.enterprise_value)
print()

print("EBIT:")
print(mrk.ebit)
print()

print("RETURN ON ENTERPRISE VALUE:")
print(str(mrk.return_on_enterprise) + "%")
print()