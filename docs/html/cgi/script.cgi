#!/usr/bin/python

import os
import cgi

form = cgi.FieldStorage()

first_name = form.getvalue('first_name', '')
surname = form.getvalue('surname', '')
message = form.getvalue('message', '')

html = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Webserv - POST Form</title>
    <link rel="stylesheet" href="styles.css">
    <link rel="icon" type="image/ico" href="icon/favicon.ico">
</head>
<body>
    <header>
        <h1>Webserv</h1>
        <nav>
            <ul>
                <li><a href="index.html">Home</a></li>
                <li><a href="contact.html" class="active">Contact</a></li>
                <li><a href="about.html">About us</a></li>
            </ul>
        </nav>
    </header>
    <main>
        <h2>Thank you for submitting the form</h2>
        <p>Here are the details you provided:</p>
        <ul>
            <li><strong>First Name:</strong> {first_name}</li>
            <li><strong>Last Name:</strong> {surname}</li>
            <li><strong>Message:</strong> {message}</li>
        </ul>
    </main>
    <footer>
        <p>&copy; 2023 My Website. All rights reserved.</p>
    </footer>
</body>
</html>
""".format(first_name=first_name, surname=surname, message=message)

print("HTTP/1.1 200 OK\nContent-type: text/html")
print("Content-length: {}\n".format(len(html)))
print("")
print(html)
