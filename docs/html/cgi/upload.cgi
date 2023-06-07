#!/usr/bin/python

import cgi, os

form = cgi.FieldStorage()

fileitem = form['file_upload']

path = "./uploads/"

isExist = os.path.exists(path)

if not isExist:
	os.makedirs(path)

if fileitem.filename:
	fn = os.path.basename(fileitem.filename)
	open(path + fn, 'wb').write(fileitem.file.read())
	print ("HTTP/1.1 200 OK\nContent-type: text/html\n")
	html_success = """
	<!DOCTYPE html>
	<html lang="en">
	<head>
	    <meta charset="UTF-8">
	    <meta name="viewport" content="width=device-width, initial-scale=1.0">
	    <title>Webserv - POST Form</title>
	    <link rel="stylesheet" href="/styles.css">
	    <link rel="icon" type="image/ico" href="/icon/favicon.ico">
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
	        <p>File Uploaded : <strong> {file_name} </strong></p>
	    </main>
	    <footer>
	        <p>&copy; 2023 My Website. All rights reserved.</p>
	    </footer>
	</body>
	</html>
	""".format(file_name=fn)
	print(html_success)

else:
	print ("HTTP/1.1 400 Bad Request\nContent-type: text/html\n")
	html_failure = """
	<!DOCTYPE html>
	<html lang="en">
	<head>
		<meta charset="UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<title>Webserv - POST Form</title>
		<link rel="stylesheet" href="/styles.css">
		<link rel="icon" type="image/ico" href="/icon/favicon.ico">
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
		<footer>
			<p>&copy; 2023 My Website. All rights reserved.</p>
		</footer>
	</body>
	</html>
	"""
	print(html_failure)

