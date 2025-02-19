import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import date

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    #get the number of cash that the user has
    user_cash_query = db.execute('SELECT cash FROM users WHERE id = ?', session['user_id'])
    if not user_cash_query or user_cash_query[0]['cash'] == None:
        return apology('Error retrieving user cash from database')
    user_cash = float(user_cash_query[0]['cash'])
    number_shares = 0
    stock_prices = []
    holdings = []
    stock_name_cursor = []
    stock_shares = []
    stock_names = []
    #get stock's name
    stock_query = db.execute('SELECT stock_name FROM purchases WHERE person_id = ? ORDER BY shares DESC', session['user_id'])
    if not stock_query:
            return render_template('index.html', user_cash=user_cash, total=user_cash)
    #check if query has values
    for stock_query_checker in stock_query:
        if not stock_query_checker['stock_name'] or stock_query_checker['stock_name'] == None:
            return apology('error retrieving stocks from database')
        stock_names.append(stock_query_checker['stock_name'])
    counter = 0
    holdings_total = 0
    #get the number of shares and get the current stock price and calculate the holding
    for stock_name in stock_names:
        #check for stock_name
        if stock_name not in stock_name_cursor:
            #get the stock in the list
            stock_name_cursor.append(stock_name)
            #get the number of shares
            number_shares_query = db.execute("SELECT shares FROM purchases WHERE person_id = ? AND stock_name = ? ORDER BY shares DESC", session['user_id'], stock_name)
            for number_shares_checker in number_shares_query:
                if not number_shares_checker['shares'] or number_shares_checker == None:
                    return apology('Error retrieving the number of shares from database')
            number_shares = int(number_shares_query[0]['shares'])
            stock_shares.append({stock_name: number_shares})
            #get the stock price and append it to the list
            stock_price_cursor = lookup(stock_name)
            if not stock_price_cursor or stock_price_cursor['price'] == None:
                return apology('error 5')
            stock_price = float(stock_price_cursor['price'])
            stock_prices.append({stock_name: stock_price})
            #get the holding of the stock
            holding = float(number_shares * stock_price)
            holdings.append({stock_name: holding})
    #get the total amount of cash from holdings
    for x in stock_name_cursor:
        holdings_total += float(holdings[counter][x])
        counter += 1
    #get total amount of money from user_cash and holdings_total
    total = float(holdings_total + user_cash)
    return render_template('index.html', stock_names=stock_names, stock_shares=stock_shares, stock_prices=stock_prices, holdings=holdings, user_cash=user_cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    #if buy was accessed with post
    if request.method == 'POST':
        if not session['user_id'] or session['user_id'] == None:
            return apology('User not found. Please log in again')
        #lookup company's info
        company = lookup(request.form.get('symbol'))
        if not company or company == None:
            return apology('Stock name does not exist')
        if not company['name'] or company['name'] == None:
            return apology('trouble getting the name of the company')
        if not company['price'] or company['price'] == None:
            return apology('trouble getting the stock price of the company')
        if not company['symbol'] or company['symbol'] == None:
            return apology('trouble getting the symbol of the company')
        stock_price = float(company['price'])
        try:
            user_cash_query = db.execute('SELECT cash FROM users WHERE id = ?', session['user_id'])
        except TypeError or ValueError:
            return apology('Invalid cash value retrived from database')
        #if cash column in the database of the user is empty
        if not user_cash_query or user_cash_query[0]['cash'] == None:
            return apology('Error retrieving the cash of the user from database')
        # Extract the cash value from the query result
        user_cash = float(user_cash_query[0]['cash'])
        #if company exists
        #try to get the number of shares
        try:
            number_shares = int(request.form.get('shares'))
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
        user_stock_shares_query = db.execute('SELECT shares FROM purchases WHERE person_id = ? AND stock_name = ?', session['user_id'], company['name'])
        #1st time the user has bought that specific stock
        time_of_action = date.today()
        if not user_stock_shares_query or user_stock_shares_query[0]['shares'] == None:
            #if the user has the money to complete the purchase
            try:
                db.execute('UPDATE users SET cash = ? WHERE id = ?', updated_cash, session['user_id'])
                db.execute('INSERT INTO purchases (person_id, stock_name, stock_price, purchase_time, shares) VALUES(?, ?, ?, ?, ?)', session['user_id'], company['name'], stock_price, time_of_action, number_shares)
                db.execute('INSERT INTO history (person_id, stock_name, type, type_price, shares, time) VALUES(?, ?, ?, ?, ?, ?)', session['user_id'], company['name'], 'Bought', stock_price, number_shares, time_of_action)
            except TypeError:
                return apology('Error finishing the purchase')
            return redirect('/')
        try:
            db.execute('INSERT INTO history (person_id, stock_name, type, type_price, shares, time) VALUES(?, ?, ?, ?, ?, ?)', session['user_id'], company['name'], 'Bought', stock_price, number_shares, time_of_action)
            db.execute('UPDATE users SET cash = ? WHERE id = ?', updated_cash, session['user_id'])
            db.execute('UPDATE purchases SET shares = ?, purchase_time = ? WHERE stock_name = ? AND person_id = ?', number_shares + int(user_stock_shares_query[0]['shares']), time_of_action, company['name'], session['user_id'])
        except TypeError:
            return apology('Error retriving data2')
        return redirect('/')
    #if buy was accessed with get
    return render_template('buy.html')


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_history_query = db.execute('SELECT * FROM history WHERE person_id = ?', session['user_id'])
    return render_template('history.html', user_history_query=user_history_query)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/password", methods=['GET', 'POST'])
@login_required
def password():
    """Change the password"""
    if request.method == 'POST':
        #get and compare the old password
        old_password = request.form.get('old')
        old_password_checker_cursor = db.execute('SELECT hash FROM users WHERE id = ?', session['user_id'])
        if not old_password:
            return apology('Must provide the old password')
        if check_password_hash(old_password_checker_cursor[0]['hash'], old_password) == False:
            return apology('Your password does not match the old one')
        #get and compare the new password
        new_password = request.form.get('new')
        confirm = request.form.get('confirm')
        if not new_password:
            return apology('You must provide a new password')
        if not confirm:
            return apology('You must confirm the new password')
        if new_password != confirm:
            return apology('New password and confirm password do not match')
        db.execute('UPDATE users SET hash = ? WHERE id = ?', generate_password_hash(new_password, method='scrypt', salt_length=16), session['user_id'])
        return render_template('success.html')
    return render_template('password.html')


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    #if i accessed quote through post
    if request.method == 'POST':
        #get company symbol and lookup it's info and stock value
        company = lookup(request.form.get('symbol'))
        #if company does not exist
        if not company:
            return apology('Stock name does not exist')
        #if company exists
        return render_template('quoted.html', company_name=company['name'], company_price=company['price'], company_symbol=company['symbol'])
    #if i accessed quote through get
    return render_template('quote.html')


@app.route("/cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Add cash"""
    #if i accessed through post
    if request.method == 'POST':
        #get cash, check for errors and update value
        try:
            cash = float(request.form.get('cash'))
        except ValueError:
            return apology('Must provide a valid number')
        if cash <= 0:
            return apology('Must provide a positive number to the form')
        user_cash_query = db.execute('SELECT cash FROM users WHERE id = ?', session['user_id'])
        updated_cash = cash + float(user_cash_query[0]['cash'])
        db.execute('UPDATE users SET cash = ? WHERE id = ?', updated_cash, session['user_id'])
        return render_template('success.html')
    #if i accessed through get
    return render_template('cash.html')


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == 'POST':
        #get the username, password and confirm password
        username = request.form.get('username')
        password = request.form.get('password')
        confirm_password = request.form.get('confirmation')
        #check if user provided the needed information and check if the username is already in the database
        if not username:
            return apology('Must provide a username')
        elif not password or not confirm_password:
            return apology('Must provide a password and confirm said password')
        elif password != confirm_password:
            return apology('Passwords are not the same')
        #insert user into the database
        try:
            db.execute('INSERT INTO users (username, hash) VALUES(?, ?)', username, generate_password_hash(password, method='scrypt', salt_length=16))
            return render_template('success.html')
        except ValueError:
            return apology('Username already exists')

    return render_template('register.html')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == 'POST':
        stock_name = request.form.get('symbol')
        number_shares = request.form.get('number_shares')
        if not stock_name:
            return apology('Must provide a stock symbol')
        try:
            number_shares = int(request.form.get('number_shares'))
        except ValueError:
            #if the input of the user is not an integer
            return apology('The number of shares must be an integer')
        #if number of shares is not a positive interger
        if number_shares < 1:
            return apology('In order to sell a share you need to input a positive integer')
        stock_checker_query = db.execute('SELECT shares FROM purchases WHERE stock_name = ? AND person_id = ?', stock_name, session['user_id'])
        if not stock_checker_query:
            return apology('You do not own the requested stock')
        company_dict = lookup(stock_name)
        updated_cash = float(number_shares * float(company_dict['price']))
        updated_shares = int(int(stock_checker_query[0]['shares']) - number_shares)
        user_cash_query = db.execute('SELECT cash FROM users WHERE id = ?', session['user_id'])
        if updated_shares < 0:
            return apology('You are attempting to sell a greater quantity of shares than you possess', 415)
        time_of_action = date.today()
        if number_shares == int(stock_checker_query[0]['shares']):
            db.execute('INSERT INTO history (person_id, stock_name, type, type_price, shares, time) VALUES(?, ?, ?, ?, ?, ?)', session['user_id'], stock_name, 'Sold', company_dict['price'], number_shares, time_of_action)
            db.execute('UPDATE users SET cash = ? WHERE id = ?', updated_cash + float(user_cash_query[0]['cash']), session['user_id'])
            db.execute('DELETE FROM purchases WHERE stock_name = ? AND person_id = ?', stock_name, session['user_id'])
            return redirect('/')
        db.execute('INSERT INTO history (person_id, stock_name, type, type_price, shares, time) VALUES(?, ?, ?, ?, ?, ?)', session['user_id'], stock_name, 'Sold', company_dict['price'], number_shares, time_of_action)
        db.execute('UPDATE users SET cash = ? WHERE id = ?', updated_cash + float(user_cash_query[0]['cash']), session['user_id'])
        db.execute('UPDATE purchases SET shares = ? WHERE stock_name = ? AND person_id = ?', updated_shares, stock_name, session['user_id'])
        return redirect('/')
    return render_template('sell.html')
