# Backlog
This is a simple log of all of the features yet to be completed and those that are desired in the future.

## Now
* Further test the Stock class, and make existing code more secure and refactored. 
* Add in multiple checks and printed error statements (as well as error handling).
* Remove or complete 'TODO' comments.
* Stress test Yahoo Finance by scraping A LOT of stocks.
    * If an error occurs, generate more user aliases and ways to rotate them.

## Should Be Thinking About
* How do we want the script to operate until a basic text-based UI or GUI is created?
    * Do we want to hard-code the stocks we are looking after?
    * Do we want separated modules/files for searching, comparing, etc. until we decide the parent point?
* Decide what the most important and useful features to implement will be.
    * Collecting information on several stocks in a manner for scalability and efficiency.
    * Comparing stocks.
    * Filtering/searching stocks.
    * Collecting historical information.
        * How should we store this information? A shared local database (will have to handle duplicate information on pushes), or a real database?
        * Is there a way to have the script(s) actually run themselves on a scheduled basis, or is that only something the user can configure through their own OS?
    * How can we make the scraping more efficient?
        * Once data is actually stored somewhere and persists, create 'update' methods that could scrape and update information that could have changed since the last scrape.

## Should Keep In Mind for Scalability and Robustness
* Prevent smelly code later on.
* Ensure cohesiveness across coding convetions.
* Find and use a unit testing library for Python.
