####################################################################################
# AUTHOR: # Devin Amdahl          # FILE: # stock_db.py                            #
# EMAIL:  # devinamdahl@gmail.com ##################################################
# DATE:   # 11/29/2022            # Testing the ability to connect to a MySQL      #
#                                 # database to populate it with the collected     #
#                                 # information. ###################################
####################################################################################

# TODO, add the use of MySQL Connector to README.md
# - mysql.connector must be installed
# - 'pip install mysql-connector-python'
import mysql.connector
from mysql.connector import Error


def connect():
    conn = None;
    try:
        conn = mysql.connector.connect(host='localhost',
                                       database='stock_scraper_363',
                                       user='stock_363',
                                       password='363')

        if conn.is_connected():
            print('Connected to MySQL database!')

    except Error as e:
        print(e)
    finally:
        if conn is not None and conn.is_connected():
            conn.close();