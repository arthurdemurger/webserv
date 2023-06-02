#!/usr/bin/python3

import cgi

# Récupère les données POST
form = cgi.FieldStorage()

# Vérifie si un champ spécifique a été envoyé
if 'nom_champ' in form:
    valeur = form['nom_champ'].value
    # Fais quelque chose avec la valeur

# Génère la réponse
print("Content-type: text/html")
print()
print("<html>")
print("<body>")
print("<h1>CGI Script</h1>")
print("</body>")
print("</html>")
