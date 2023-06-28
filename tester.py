#!/usr/bin/python3

import subprocess

# URL de votre serveur
server_url = "http://localhost:80"

# Fonction pour effectuer une requête POST avec curl
def perform_post_request():
    endpoint = "/cgi-bin/contact.cgi"  # Endpoint pour la requête POST
    data = {
        "first_name": "first_name",
        "last_name": "last_name",
        "email": "test@gmail.com",
        "message": "test message"
    }  # Données du formulaire

    # Construction de la commande curl
    curl_command = f'curl -X POST -d "first_name={data["first_name"]}&last_name={data["last_name"]}&email={data["email"]}&message={data["message"]}" -w "\n%{{http_version}} %{{http_code}}\n" {server_url}{endpoint}'

    # Exécution de la commande curl
    result = subprocess.run(curl_command, shell=True, capture_output=True, text=True)

    # Extraction du code de statut HTTP et de la ligne d'état
    response_lines = result.stdout.strip().split("\n")
    http_version, status_code = response_lines[-1].split()
    http_status = " ".join(response_lines[-1].split()[2:])

    # Affichage du statut HTTP
    print("Requête POST - Code de statut HTTP :", status_code)

# Fonction pour effectuer une requête GET avec curl
def perform_get_request():
    endpoint = "/index.html"  # Endpoint pour la requête GET

    # Construction de la commande curl
    curl_command = f'curl -w "\n%{{http_version}} %{{http_code}}\n" {server_url}{endpoint}'

    # Exécution de la commande curl
    result = subprocess.run(curl_command, shell=True, capture_output=True, text=True)

    # Extraction du code de statut HTTP et de la ligne d'état
    response_lines = result.stdout.strip().split("\n")
    http_version, status_code = response_lines[-1].split()
    http_status = " ".join(response_lines[-1].split()[2:])

    # Affichage du statut HTTP
    print("Requête GET", endpoint, "- Code de statut HTTP :", status_code)

# Exemple d'utilisation
perform_post_request()
perform_get_request()