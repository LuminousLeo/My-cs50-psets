import os

from cs50 import SQL
from helpers import apology, login_required, lookup, usd
from datetime import date

db = SQL("sqlite:///finance.db")


#lookup company's info
def test():
    company = 'NFLX'
    if not company:
        return apology('Stock name does not exist')
    stock_price = float(453.9)
    try:
        user_cash_query = db.execute('SELECT cash FROM users WHERE id = ?', 18)
    except TypeError:
        return apology('Invalid cash value retrived from database')
    user_cash_query = db.execute('SELECT cash FROM users WHERE id = ?', 18)
    #if cash column in the database of the user is empty
    if not user_cash_query:
        return apology('User not found or cash not available')
    # Extract the cash value from the query result
    try:
        user_cash = float(user_cash_query[0]['cash'])
    except TypeError:
        return apology('Invalid cash value retrived from database')
    #if company does not exist
    if not company:
        return apology('Stock name does not exist')
    #if company exists
    #try to get the number of shares
    try:
        number_shares = int(3)
    except ValueError:
        #if the input of the user is not an integer
        return apology('The number of shares must be an integer')
    #if number of shares is not a positive interger
    if number_shares < 1:
        return apology('In order to buy a share you need to input a positive integer')
    #if user does not have enouth money to the shares of the stock
    holding = float(stock_price * number_shares)
    if user_cash < holding:
        return apology('Not enough money to complete the purchase')
    updated_cash = float(user_cash - holding)
    #check if the user already has the stock
    user_stock_shares_query = db.execute('SELECT shares FROM purchases WHERE person_id = ? AND stock_name = ?', 18, company)
    #1st time the user has bought that specific stock
    time_of_action = date.today()
    if not user_stock_shares_query:
        #if the user has the money to complete the purchase
        db.execute('UPDATE users SET cash = ?', updated_cash)
        db.execute('INSERT INTO purchases (person_id, stock_name, stock_price, purchase_time, shares) VALUES(?, ?, ?, ?, ?)', 18, company, stock_price, time_of_action, number_shares)
        db.execute('INSERT INTO history (person_id, stock_name, type, type_price, shares, time) VALUES(?, ?, ?, ?, ?, ?)', 18, company, 'Bought', stock_price, number_shares, time_of_action)
        return redirect('/')
    db.execute('INSERT INTO history (person_id, stock_name, type, type_price, shares, time) VALUES(?, ?, ?, ?, ?, ?)', 18, company, 'Bought', stock_price, number_shares, time_of_action)
    db.execute('UPDATE users SET cash = ?', updated_cash)
    db.execute('UPDATE purchases SET shares = ?, purchase_time = ? WHERE stock_name = ?', number_shares + int(user_stock_shares_query[0]['shares']), time_of_action, company)
    print('ok')
    return


test()

