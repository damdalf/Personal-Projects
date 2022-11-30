####################################################################################
# AUTHOR: # Devin Amdahl          # FILE: # toolbox.py                          #
# EMAIL:  # devinamdahl@gmail.com ##################################################
# DATE:   # 07/29/2022            # Provides several utility functions that do not #
################################### directly relate to the Stock class             #
####################################################################################

def inserter(s, a, n):
    """
    s: The original string
    a: The characters you want to append
    n: The position you want to append the characters
    """
    return s[:n] + a + s[n:]
