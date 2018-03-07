from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    
    
    #db.execute("UPDATE Assets SET Price = :price1 + (:price) WHERE userid = (:baron) AND symbol = (:symbol)",  price1=ticks[0]["Price"], price=cost['price'], baron=session["user_id"], symbol=cost["symbol"])
    
    cashking = db.execute("SELECT cash FROM users WHERE id = :username", username=session["user_id"])
    print(cashking)
    stocks = db.execute("SELECT name, symbol, shares, Price, total FROM Assets WHERE userid = :username", username=session["user_id"])
    simba = db.execute("SELECT Sum(total) FROM Assets WHERE userid = :username", username=session["user_id"])
    bae = db.execute("SELECT symbol FROM Assets WHERE userid = :username", username=session["user_id"])
    #bae = db.execute("SELECT symbol, Sum(quantity) AS quantities FROM portfolio WHERE user_id_fk = :user_id_fk GROUP BY stock, symbol ORDER BY stock", user_id_fk = session["user_id"])
    
    #print(lookup(bae[0]["symbol"]))
    
    #for symbol in stocks:
    #    dough = lookup(stocks["symbol"])
     #   print(dough["price"])
    if simba[0]["Sum(total)"] != None:
        fresh = simba[0]["Sum(total)"] + cashking[0]["cash"]
    else:
        fresh = 0
    
    #print(fresh)
        
    
    
    
    
    return render_template("index.html", cashmoney=cashking[0]["cash"], stocks=stocks, freshy=fresh)
    #return apology("TODO")

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST":
        
        if not request.form.get("Symbol"):
            return apology("must provide stock symbol")
        
        x = request.form.get("Symbol")
        x.upper()
        print(x.upper())
        if not request.form.get("Shares"):
            return apology("must provide shares amount")
        
        cost = lookup(request.form.get("Symbol"))
        
        if cost == None:
            return apology("must provide existing stock")
        bucks = db.execute("SELECT cash FROM users WHERE id = :username", username=session["user_id"])
        print(bucks[0]['cash'])
       
        stockp = int(cost['price'])
        numshar = int(request.form.get('Shares'))
        costly = stockp * numshar
        if costly == 0:
            return apology("must provide existing stock")
        print (session["user_id"])
        print (stockp)
        print (numshar)
        tom = bucks
        print(tom)
        
        if (costly > bucks[0]['cash']):
            return apology("sorry you're too poor")
    
        ticks = db.execute("SELECT * FROM Assets WHERE userid = :username AND symbol = :symbology", username=session["user_id"], symbology=x.upper())
        print(ticks)
        print(x.upper())
        for rows in ticks:
            print(rows["symbol"])
            print(x.upper())
            if x.upper() not in rows:
                db.execute("UPDATE Assets SET shares = :shares1 + (:shares) WHERE userid = (:baron) AND symbol = (:symbol)", shares1=ticks[0]["shares"], shares=request.form.get('Shares'), baron=session["user_id"], symbol=cost["symbol"])
                db.execute("UPDATE Assets SET Price = :price1 + (:price) WHERE userid = (:baron) AND symbol = (:symbol)",  price1=ticks[0]["Price"], price=cost['price'], baron=session["user_id"], symbol=cost["symbol"])
                db.execute("UPDATE Assets SET total = :total1 + (:total) WHERE userid = (:baron) AND symbol = (:symbol)", total1=ticks[0]["total"], total=costly, baron=session["user_id"], symbol=cost["symbol"])
                db.execute("UPDATE users SET cash = cash - (:cost) WHERE id = (:baron)", cost=costly, baron=session["user_id"])
                db.execute("INSERT INTO history (userident, symbol, shares, price) VALUES(:userident, :symbol, :shares, :price)", userident=session["user_id"], symbol=cost["symbol"], shares=request.form.get('Shares'), price=cost['price'])
                return redirect(url_for("index"))
                
        db.execute("INSERT INTO Assets (userid, symbol, name, shares, price, total) VALUES(:userid, :symbol, :name, :shares, :price, :total)", userid=session["user_id"], symbol=cost["symbol"], name=cost["name"], shares=request.form.get('Shares'), price=cost['price'], total=costly)           
        db.execute("INSERT INTO history (userident, symbol, shares, price) VALUES(:userident, :symbol, :shares, :price)", userident=session["user_id"], symbol=cost["symbol"], shares=request.form.get('Shares'), price=cost['price'])
        db.execute("UPDATE users SET cash = cash - (:cost) WHERE id = (:baron)", cost=costly, baron=session["user_id"])
        return redirect(url_for("index"))

    else: 
        return render_template("buy.html")
    
    #return apology("TODO")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""

    
    
    
    
    stocks = db.execute("SELECT transacted, symbol, price, shares FROM history WHERE userident = :username", username=session["user_id"])
    #stocks = db.execute("SELECT stock, symbol, Sum(quantity) AS quantities FROM portfolio WHERE user_id_fk = :user_id_fk GROUP BY stock, symbol ORDER BY stock", user_id_fk = session["user_id"])
    
    
    
    
    
    #ereturn render_template("index.html", cashmoney=cashking[0]["cash"], stocks=stocks)
    return render_template("history.html", stocks=stocks)
    #return apology("TODO")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        
        if not request.form.get("Symbol"):
            return apology("must provide stock symbol")
        
        quotes = lookup(request.form.get("Symbol"))
        print(quotes)
        if quotes == None:
            #return render_template("quote.html")
            return apology("must provide existing stock")
        #return render_template("quoted.html")
        else:
            #return redirect(url_for("quoted"))
            return render_template("quoted.html", price=quotes["price"], stock=quotes["name"], ticker=quotes["symbol"])
            #return render_template("quoted.html", ticker=quotes["ticker"])
    else: 
        return render_template("quote.html")
    
@app.route("/quoted", methods=["GET"])
@login_required
def quoted():
    return render_template("quoted.html", price="price", ticker="ticker", stock="quote")
    #return render_template("quotedisplay.html", ticker="quote")
    #return render_template("quotedisplay.html", stock="quote")   
    
   # return apology("TODO")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    
    # forget any user_id
    session.clear()
    
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        
        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")
        
        #ensure password confirmation submitted
        elif not request.form.get("confirm password"):
            return apology("must confirm password")
        
        # query db for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        
        #ensure username is available
        if len(rows) != 0:
            return apology("username not available, please try again")
        
        #ensure passwords match
        if request.form.get("password") != request.form.get("confirm password"):
            return apology("passwords do not match, please try again")
        
        #hash passwrod
        hash = pwd_context.encrypt(request.form.get("password"))
        
        db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form.get('username'), hash=hash)
        
        
        #if fails:
            #return apology("username not available")
        
        #log user in automatically and remember who user is
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        session["user_id"] = rows[0]["id"]
        #db.execute("INSERT INTO Portfolio (userid, symbol, total) VALUES(:userid, :symbol, :total)", userid="1", symbol="CASH", total="10,000")
        #db.execute("INSERT INTO Portfolio (userid, symbol, total) VALUES(:userid, :symbol, :total)", userid=session["user_id"], symbol="CASH", total="10,000")
        return redirect(url_for("index"))
        
        
    else:
        return render_template("register.html")
    
    
    #return apology("TODO")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == "POST":
        
        if not request.form.get("Symbol"):
            return apology("must provide stock symbol")
        
        x = request.form.get("Symbol")
        x.upper()
        print(x.upper())
        if not request.form.get("Shares"):
            return apology("must provide shares amount")
        
        cost = lookup(request.form.get("Symbol"))
        #y -= request.form.get("Shares")
        
        
        #print(y)
        print("hello")
        if cost == None:
            return apology("must provide existing stock")
        #jeff = session["user_id"]
        bucks = db.execute("SELECT cash FROM users WHERE id = :username", username=session["user_id"])
        print(bucks[0]['cash'])
       
        #print(bucks['price'])
        #for column in bucks:
        #print (column[1])
        stockp = int(cost['price'])
        numshar = int(request.form.get('Shares'))
        numshard = -int(request.form.get('Shares'))
        costly = stockp * numshar
        if costly == 0:
            return apology("must provide existing stock")
        print (session["user_id"])
        print (stockp)
        print (numshar)
        tom = bucks
        yass = 0
        yass = yass - numshar
        print(numshard)
        print(tom)
        
        
        #if (costly > bucks[0]['cash']):
         #   return apology("sorry you're too poor")
        
        
        ticks = db.execute("SELECT * FROM Assets WHERE userid = :username AND symbol = :symbology", username=session["user_id"], symbology=x.upper())
        for rows in ticks:
            if x.upper() == rows["symbol"]:
                    db.execute("UPDATE Assets SET shares = :shares1 - (:shares) WHERE userid = (:baron) AND symbol = (:symbol)", shares1=ticks[0]["shares"], shares=numshar, baron=session["user_id"], symbol=cost["symbol"])
                    db.execute("UPDATE Assets SET Price = :price1 - (:price) WHERE userid = (:baron) AND symbol = (:symbol)",  price1=ticks[0]["Price"], price=cost['price'], baron=session["user_id"], symbol=cost["symbol"])
                    db.execute("UPDATE Assets SET total = :total1 - (:total) WHERE userid = (:baron) AND symbol = (:symbol)", total1=ticks[0]["total"], total=costly, baron=session["user_id"], symbol=cost["symbol"])
                    db.execute("INSERT INTO history (userident, symbol, shares, price) VALUES(:userident, :symbol, :shares, :price)", userident=session["user_id"], symbol=cost["symbol"], shares=yass, price=cost['price'])
                    db.execute("UPDATE users SET cash = cash + (:cost) WHERE id = (:baron)", cost=costly, baron=session["user_id"])
                    #db.execute("UPDATE Assets SET ((shares = :shares1 + :shares), (Price = :price1 + :price), (total = :total1 + :total)) WHERE id = (:baron) AND symbol = (:symbol)", shares1=ticks[0]["shares"], price1=ticks[0]["Price"], total1=ticks[0]["total"], shares=request.form.get('Shares'), price=cost['price'], total=costly, baron=session["user_id"], symbol=cost["symbol"])
                    #db.execute("UPDATE Assets SET shares = :shares, Price = :price, total = :total WHERE userid = (:baron) AND symbol = (:symbol)", shares=request.form.get('Shares'), price=cost['price'], total=costly, baron=session["user_id"], symbol=cost["symbol"])
                    return redirect(url_for("index"))
            else:
                    #db.execute("INSERT INTO Assets (userid, symbol, name, shares, price, total) VALUES(:userid, :symbol, :name, :shares, :price, :total)", userid=session["user_id"], symbol=cost["symbol"], name=cost["name"], shares=x, price=cost['price'], total=costly)
                    #db.execute("INSERT INTO history (userident, symbol, shares, price) VALUES(:userident, :symbol, :shares, :price)", userident=session["user_id"], symbol=cost["symbol"], shares=request.form.get('Shares'), price=cost['price'])
                    #db.execute("UPDATE users SET cash = cash + (:cost) WHERE id = (:baron)", cost=costly, baron=session["user_id"])
                    return redirect(url_for("index"))
        #return render_template("index.html")
    
    else: 
        return render_template("sell.html")
    #return apology("TODO")
