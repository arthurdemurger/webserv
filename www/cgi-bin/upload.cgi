#!/usr/bin/python

import os, cgi, sys

form = cgi.FieldStorage()

fileitem = form['file_upload']

path = "www/upload/"
port = os.environ.get('SERVER_PORT')
server_name = os.environ.get('SERVER_NAME')

isExist = os.path.exists(path)

if not isExist:
	os.makedirs(path)

if fileitem.filename:
	fn = os.path.basename(fileitem.filename)
	dest_path = os.path.join(path, fn)
	open(dest_path, 'wb').write(fileitem.file.read())

	print("HTTP/1.1 200 OK\nContent-type: text/html\n")
	html_success = """
	<!DOCTYPE html>
	<html lang="en">
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
		<h2 class="title">Upload</h2>
		<section id="form-section">
			<div class="form-container">
				<h2>Submit form</h2>
				<div class="message-container">
					<h3> File uploaded ! </h3>
				</div>
			</div>
	</section>
	</body>
	</html>
	"""
	print(html_success)

else:
	print("HTTP/1.1 400 Bad Request\nContent-type: text/html\n")
	html_failure = """
	<!DOCTYPE html>
	<html lang="en">
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
		<main>
			<p>No file uploaded.</p>
		</main>
	</body>
	</html>
	"""
	print(html_failure)
