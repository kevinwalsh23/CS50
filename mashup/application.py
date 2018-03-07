import os
import re
from flask import Flask, jsonify, render_template, request, url_for
from flask_jsglue import JSGlue

from cs50 import SQL
from helpers import lookup

# configure application
app = Flask(__name__)
JSGlue(app)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///mashup.db")

@app.route("/")
def index():
    """Render map."""
    #if not os.environ.get("API_KEY"):
    #    raise RuntimeError("API_KEY not set")
    return render_template("index.html", key=("AIzaSyBIIlDV4OQSS2z2OXbilqg8HXs44AVv710"))

@app.route("/articles", methods=["GET"])
def articles():
    if request.method == "POST":
         raise RuntimeError("Invalid Method")
    else:
        x = request.args.get("geo")
        if x == None:
            raise RuntimeError("Invalid Geo")
        else:
            y = lookup(x)
        
                    
    
    
    
    """Look up articles for geo."""

    # TODO
    #print("asdf")
    frankbuick = jsonify(y)
    
    return frankbuick
    

@app.route("/search", methods=["GET"])
def search():
    #if request.method == "POST":
     #    raise RuntimeError("Invalid Method")
    #else:
     #   x = request.args.get("geo")
      #  if x == None:
       #     raise RuntimeError("Invalid Geo")
        #else:
    q = request.args.get("q") + "%"
    #print(x is {}.format(x))
    bucks = db.execute("SELECT * FROM places WHERE postal_code LIKE :q OR place_name LIKE :q OR admin_name1 LIKE :q LIMIT 10 ", q=q)
     #   y = lookup(x)
    #print(bucks)
    #placde[] == bucks
    #for row in bucks:  
        #place[row]
    """Search for places that match query."""
   # for rows in bucks:
      # print(rows["place_name"])
    # TODO
    #return 5
    #print(jsonify([bucks]))
    #return bucks
    #print (bucks.place_name)
    
    placed = jsonify(bucks)
    #print(places)
    return placed
    #print(clams)
    #Qreturn clams
    #return 
@app.route("/update")
def update():
    """Find up to 10 places within view."""

    # ensure parameters are present
    if not request.args.get("sw"):
        raise RuntimeError("missing sw")
    if not request.args.get("ne"):
        raise RuntimeError("missing ne")

    # ensure parameters are in lat,lng format
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("sw")):
        raise RuntimeError("invalid sw")
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("ne")):
        raise RuntimeError("invalid ne")

    # explode southwest corner into two variables
    (sw_lat, sw_lng) = [float(s) for s in request.args.get("sw").split(",")]

    # explode northeast corner into two variables
    (ne_lat, ne_lng) = [float(s) for s in request.args.get("ne").split(",")]

    # find 10 cities within view, pseudorandomly chosen if more within view
    if (sw_lng <= ne_lng):

        # doesn't cross the antimeridian
        rows = db.execute("""SELECT * FROM places
            WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude AND longitude <= :ne_lng)
            GROUP BY country_code, place_name, admin_code1
            ORDER BY RANDOM()
            LIMIT 10""",
            sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng)
        
    else:

        # crosses the antimeridian
        rows = db.execute("""SELECT * FROM places
            WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude OR longitude <= :ne_lng)
            GROUP BY country_code, place_name, admin_code1
            ORDER BY RANDOM()
            LIMIT 10""",
            sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng)
       
    # output places as JSON
    #print(rows)
    return jsonify(rows)
