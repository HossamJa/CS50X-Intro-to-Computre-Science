import os

import sqlite3
from datetime import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)


# Define the absolute path for the database file
db_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "finance.db")
# Check if the database file exists, otherwise create one
if not os.path.exists(db_path):
    conn = sqlite3.connect(db_path)
    conn.close()

# Configure CS50 Library to use SQLite database
db = SQL(f"sqlite:///{db_path}")

# Create the users table if its not there
db.execute("""
CREATE TABLE IF NOT EXISTS users (
           id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
           username TEXT NOT NULL, 
           hash TEXT NOT NULL, 
           cash NUMERIC NOT NULL DEFAULT 10000.
        );
""")

db.execute("""
    CREATE UNIQUE INDEX IF NOT EXISTS username ON users (username);
""")

# Create history table to store user history purchases
db.execute("""
    CREATE TABLE IF NOT EXISTS history (
        user_id INTEGER,
        action TEXT NOT NULL,
        symbol TEXT NOT NULL,
        shares INTEGER NOT NULL,
        share_price NUMERIC NOT NULL,
        total_price NUMERIC NOT NULL,
        datetime DATE NOT NULL,
        FOREIGN KEY (user_id) REFERENCES users(id)
    );
""")

# To store the quoted values from lookup
QUOTES = []

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

    # Get the current user id 
    USER_ID = session.get("user_id")

    # Get Username and cash balance of the current user 
    username = db.execute("SELECT username FROM users WHERE id = ?", USER_ID)[0]["username"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", USER_ID)[0]["cash"]
    # Get all the stock symbols owned by the current user
    owned_stocks = db.execute("SELECT DISTINCT symbol FROM history WHERE user_id = ?", USER_ID)

    # initiate an empty list to store the current stocks data 
    records = []
    # initiate a variable to stor the sum of all the stocks's total prices
    shares_total_value = 0

    for stock in owned_stocks:

        # Get the Symbol of the stock 
        symbol = stock["symbol"]
        # Get the number of shares owned of that stock 
        shares = db.execute("SELECT sum(shares) AS shares_number FROM history WHERE user_id = ? AND symbol = ?", USER_ID, symbol)[0]["shares_number"]
        
        # Check if the user have any shares of that stock
        if shares < 1:
            continue # if there is no shares left skip and don't show it
        
        # Get the most new stock price
        stock_data = lookup(symbol)
        share_price = stock_data["price"]

        # Calculate the total value of shares owned of that stock
        total_price = shares * share_price
        # Add the total value to the sum of all the shares value
        shares_total_value += total_price

        # Create a record dict and append it to the list
        record = {
            "symbol" : symbol,
            "shares" : shares,
            "share_price" : usd(share_price),
            "total_price" : usd(total_price),
        }
        records.append(record)

    # Calculate the garnd total value the user have 
    value_total = shares_total_value + cash
    
    # Create a user data dict 
    user_data = {
        "username": username,
        "cash": usd(cash),
        "total": usd(value_total),
        "total_shares_value": usd(shares_total_value),
    }
    return render_template("index.html", records=records, user_data=user_data)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # Get the current user id 
    USER_ID = session.get("user_id")
       
    # get the user's cash
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", USER_ID)[0]["cash"]

    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Symbol must be provided")
        shares = request.form.get("shares")
        if not shares:
            return apology("Shares Number must not be empty!")
        try:
            shares = int(shares)
            if shares <= 0:
                return apology("Invalid number of shares")
        except ValueError:
            return apology("Invalid Number Of shares!")
        # get the current price of that stock
        quote_data = lookup(symbol)

        if quote_data is None:
            return apology("The symbol does not exist!")
        share_price = quote_data["price"]
        # The total price to pay
        total_price = shares * share_price
        # Check if the user' cash can pay the total price
        if user_cash < total_price:
            return apology("No enough cash!")
        # substract the total price from user's cash
        remain_cash = user_cash - total_price
        # Get the date and time 
        date_time = datetime.now()
        # Update the user's cash in db
        db.execute("UPDATE users SET cash = ? WHERE id = ?", remain_cash, USER_ID)
        # Store all the purchase in db
        db.execute("INSERT INTO history (user_id, action, symbol, shares, share_price, total_price, datetime) VALUES (?, ?, ?, ?, ?, ?, ?)", USER_ID,  "BUY", symbol, shares, share_price, -total_price, date_time)

        return redirect("/")
    # Handle the get request if args are sent 
    stock_to_buy = request.args.get("symbol")
    if not stock_to_buy:
        stock_to_buy = ""
    
    return render_template("buy.html", cash_balance=usd(user_cash), symbol=stock_to_buy)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Get the current user id 
    USER_ID = session.get("user_id")
    records = db.execute("SELECT * FROM history WHERE user_id = ?", USER_ID)
    for record in records:
        record["share_price"] = usd(record["share_price"])
        record["total_price"] = usd(record["total_price"])
    return render_template("history.html", records=records)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


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
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Stock Symbol Can't Be Empty")
        quote_data = lookup(symbol)
        if quote_data is None:
            return apology("Invalid Symbol")
        quote_data["price"] = usd(quote_data["price"])
        QUOTES.append(quote_data)

    return render_template("quote.html", quotes=QUOTES)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Get the username 
        username = request.form.get("username")
        # Check if the username is not blank
        if not username:
            return apology("Username is empty!")
        
        # Get the password
        password = request.form.get("password")
        # Check if the password is not blank
        if not password:
            return apology("Password is empty!")
        # Get password confirmation
        confirmation = request.form.get("confirmation")
        # Check if confirmation is not empty
        if not confirmation:
            return apology("Please confirm your password.")
        
        # Check if the password and confirmation match
        if confirmation != password:
            return apology("Password and Confirmation Don't Match")
        try:
            # Generate hash for the password to store it in db
            hash = generate_password_hash(password)
            # Store the username and pwhash in db
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
            
            return redirect("/")
        
        except ValueError: # If the username already exist
            return apology("This username already exists.")
    
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Get the current user id 
    USER_ID = session.get("user_id")
    # Get all the stock symbols owned by the current user
    owned_stocks = db.execute("SELECT DISTINCT symbol FROM history WHERE user_id = ?", USER_ID)
    stocks_list = []
    for stock in owned_stocks:
        stocks_list.append(stock["symbol"])

    # Check http request
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol or not shares:
            return apology("Mssing Stock Symbol Or The Number Of Shares!")
        
        # check submitted stock is a avlid owned stock by the user
        if symbol not in stocks_list:
            return apology("you don't own that stock!")
        
        owned_shares = db.execute("SELECT sum(shares) AS total_shares FROM history WHERE user_id = ? AND symbol = ?", USER_ID, symbol)[0]["total_shares"]

        try:
            shares = int(shares)
            if shares <= 0:
                 return apology("Shares must be a positive number.")
            if shares > owned_shares:
                return apology("You don't have that many shares of that Stock!")
    
        except ValueError:
            # Handle error: Shares is not a valid integer
            return apology("Invalid number of shares.")
        
        # Get the current price of that stock
        stock_data = lookup(symbol)

        sell_price = int(shares) * stock_data["price"]
        # Get the date and time of the transaction
        date_time = datetime.now()
        # Record the sell transaction
        db.execute("INSERT INTO history (user_id, action, symbol, shares, share_price, total_price, datetime) VALUES (?, ?, ?, ?, ?, ?, ?)", USER_ID, "SELL", symbol, -shares, stock_data["price"], sell_price, date_time)
        
        # Update the user's cash balance
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", USER_ID)[0]["cash"]
        new_cash = user_cash + sell_price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, USER_ID)
      
        return redirect("/")

    return render_template("sell.html", stocks=stocks_list)


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """View and Add more cash"""
    # Get the current user id 
    USER_ID = session.get("user_id")
    message = {
        "message": "",
    }
    # Get user data: cash and username 
    user_data = db.execute("SELECT cash, username FROM users WHERE id = ?", USER_ID)[0]
    # Get user cash as float for operations
    current_cash = user_data["cash"]
    # Format the user cash for display
    user_data["cash"] = usd(user_data["cash"])

    if request.method == "POST":
        cash_amount = request.form.get("amount_cash")
        if not cash_amount or float(cash_amount) < 0.01:
            return apology("Invalid Amount of cash!")

        new_cash = current_cash + float(cash_amount)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, USER_ID)

        message["message"] = f"Deposited {usd(float(cash_amount))} To Your Account Successfully"
    
    return render_template("founds.html", user_data=user_data, message=message)


@app.route("/account", methods=["GET", "POST"])
@login_required
def account():
    """Manage account info"""
    # Get the current user id 
    USER_ID = session.get("user_id")
    username = db.execute("SELECT username FROM users WHERE id = ?", USER_ID)[0]["username"]
    user_data = {
        "username": username,
    }
    message = {
        "message": "",
        }
    if request.method == "POST":
        current_pw = request.form.get("current_pw")
        new_pw = request.form.get("new_pw")
        confirm_pw = request.form.get("confirm_pw")
        if not current_pw or not new_pw or not confirm_pw:
            return apology("Missing a field!")

        current_hash = db.execute("SELECT hash FROM users WHERE id = ?", USER_ID)[0]["hash"]

        if not check_password_hash(current_hash, current_pw):
            return apology("Incorrect Password!")
        if new_pw != confirm_pw:
            return apology("New Password don't Match Confirmation Password!")
        
        new_hash = generate_password_hash(new_pw)
        
        db.execute("UPDATE users SET hash = ? WHERE id = ?", new_hash, USER_ID)
        
        message["message"] = "Password Changed Successfully!"
        render_template("account.html", user_data=user_data, message=message)
    return render_template("account.html", user_data=user_data, message=message)
