import os
import sqlite3
from cs50 import SQL
from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Define the absolute path for the database file
db_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "birthdays.db")
# Check if the database file exists, otherwise create one
if not os.path.exists(db_path):
    conn = sqlite3.connect(db_path)
    conn.close()

# Configure CS50 Library to use SQLite database
db = SQL(f"sqlite:///{db_path}")

# Create the birhtday table if its not there
db.execute("""
    CREATE TABLE IF NOT EXISTS birthdays (
    id INTEGER,
    name TEXT,
    day INTEGER,
    month INTEGER,
    year INTEGER,
    PRIMARY KEY(id)
    );
""")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # Add the user's entry into the database
        name = request.form.get("name")
        if not name:
            return redirect("/")
        bdate = request.form.get("bdate").split("-") # Type Date in HTML form
        if not bdate:
            return redirect("/")

        db.execute("INSERT INTO birthdays (name, day, month, year) VALUES(?, ?, ?, ?)", name, int(bdate[2]), int(bdate[1]), int(bdate[0])) # Name, Year, Month, Day
        return redirect("/")

    else:

        # Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays ORDER BY month, day")

        return render_template("index.html", birthdays=birthdays)


@app.route('/update/<int:id>', methods=['PUT', 'POST'])
def update_birthday(id):
    
    if request.method == "POST":
        # Handle the form submission deletion request from HTML form
        db.execute("DELETE FROM birthdays WHERE id = ?", id)
        return jsonify({"status": "success", "message": "Deleted via POST"})


    elif request.method == "PUT":
        # This handles the in-place "Save" button from JS fetch()

        data = request.get_json()
        if not data:
            return jsonify({"status": "error", "message": "No data provided"}), 400

        try:
            name = data["name"]
            # Split the YYYY-MM-DD string
            year, month, day = data['birthday'].split('-')

            # update the data in database
            db.execute("UPDATE birthdays SET name = ?, day = ?, month = ?, year = ? WHERE id = ?", name, int(day), int(month), int(year), int(id))
            
            return jsonify({"status": "success", "message": "Record updated"})

        except Exception as e:
            # Handle potential errors gracefully
            return jsonify({"status": "error", "message": str(e)}), 500
    
    # If a GET request somehow hits this endpoint
    return jsonify({"status": "error", "message": "Invalid request method"}), 405


