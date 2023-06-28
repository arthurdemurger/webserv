#!/usr/bin/python

import os
import cgi

form = cgi.FieldStorage()

first_name = form.getvalue('first_name', '')
last_name = form.getvalue('last_name', '')
message = form.getvalue('message', '')
email = form.getvalue('email', '')

messages_dir = 'messages/'
if not os.path.exists(messages_dir):
    os.makedirs(messages_dir)

file_name = os.path.join(messages_dir, first_name)

with open(file_name, 'w') as file:
    file.write("First Name: {}\n".format(first_name))
    file.write("Last Name: {}\n".format(last_name))
    file.write("Email: {}\n".format(email))
    file.write("Message: '{}'\n".format(message))

html = """
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Webserv - POST Form</title>
    <link rel="stylesheet" href="/styles.css">
    <link rel="icon" type="image/ico" href="/favicon.ico">
</head>
<body>
    <header>
        <h1>Webserv</h1>
        <nav>
            <ul>
                <li><a href="/index.html">Home</a></li>
                <li><a href="/contact.html" class="active">Contact</a></li>
                <li><a href="/upload.html">Upload</a></li>
                <li><a href="/about.html">About us</a></li>
            </ul>
        </nav>
    </header>

	<h2 class="title">Contact</h2>
    <section id="form-section">
        <div class="form-container">
            <h2>Submit form</h2>
			<div class="message-container">
            	<h3> Message sent ! </h3>
			</div>
        </div>
    </section>
</body>
</html>
"""

print("HTTP/1.1 200 OK\nContent-type: text/html")
print("Content-length: {}\n".format(len(html)))
print("")
print(html)