from flask import Flask, redirect, render_template, request, url_for

import os
import sys
import helpers
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")
    
    positive, negative, neutral = 0.0, 0.0, 100.0
    
    analyzer = Analyzer(positives, negatives)
    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name)
    #if tweets != None:
    for i in tweets:
        score = analyzer.analyze(i) 
        if score > 0.0:
            positive += 1.0
            neutral - 1.0
        elif score < 0.0:
            negative += 1.0
            neutral - 1.0
    #else:
    #   return redirect(url_for("index")
    
    #positive, negative, neutral = 0.0, 0.0, 100.0
    
    #if score > 0.0:
     #   positive += 1.0
      #  neutral - 1.0
    #elif score < 0.0:
     #   negative -= 1.0
      #  neutral - 1.0
    print(positive)
    
    

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
