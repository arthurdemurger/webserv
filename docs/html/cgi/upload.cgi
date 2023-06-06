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
	message = "The file '" + fn + "' was uploaded successfully with python"

else:
	message = "No file was uploaded"

print ("HTTP/1.1 200 OK\nContent-type: text/html\n")
print ("<html><body><p>%s</p></body></html>""" % (message, ))