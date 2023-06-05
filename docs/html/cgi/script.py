#!/usr/bin/env python

import cgi

form = cgi.FieldStorage()
first_name = form.getvalue('first_name')
surname = form.getvalue('surname')
message = form.getvalue('message')

print("HTTP/1.1 200 OK\nContent-type: text/html\n\n")
print("<!DOCTYPE html>")
print("<html lang='fr'>")
print("<head>")
print("<meta charset='UTF-8'>")
print("<title>Webserv - POST Form Submission</title>")
print("<link rel='stylesheet' href='styles.css'>")
print("<link rel='icon' type='image/ico' href='icon/favicon.ico'>")
print("</head>")
print("<body>")
print("<header>")
print("<h1>Webserv</h1>")
print("<nav>")
print("<ul>")
print("<li><a href='index.html'>Home</a></li>")
print("<li><a href='contact.html' class='active'>Contact</a></li>")
print("<li><a href='about.html'>About us</a></li>")
print("</ul>")
print("</nav>")
print("</header>")
print("<h2 class='title'>Contact</h2>")
print("<section id='form-section'>")
print("<div class='form-container'>")
print("<h2>Form Submission Confirmation</h2>")
print("<p>First Name: {}</p>".format(first_name))
print("<p>Surname: {}</p>".format(surname))
print("<p>Message: {}</p>".format(message))
print("</div>")
print("</section>")
print("<footer>")
print("<p>&copy; 2023 Webserv. All rights reserved.</p>")
print("</footer>")
print("</body>")
print("</html>")
