#!/usr/bin/python3

import subprocess, os

# URL de votre serveur
server_url = "http://localhost:80"

# Fonction pour effectuer une requête POST avec curl
def perform_post_request(endpoint):
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
    print(f"POST {endpoint} => response : HTTP", status_code)

# Fonction pour effectuer une requête GET avec curl
def perform_get_request(endpoint):
    # Construction de la commande curl
    curl_command = f'curl -w "\n%{{http_version}} %{{http_code}}\n" {server_url}{endpoint}'

    # Exécution de la commande curl
    result = subprocess.run(curl_command, shell=True, capture_output=True, text=True)

    # Extraction du code de statut HTTP et de la ligne d'état
    response_lines = result.stdout.strip().split("\n")
    http_version, status_code = response_lines[-1].split()
    http_status = " ".join(response_lines[-1].split()[2:])

    # Affichage du statut HTTP
    print(f"GET {endpoint} - HTTP", status_code)

# Fonction pour effectuer une requête DELETE avec curl
def perform_delete_request(endpoint):
    # Construction de la commande curl
    curl_command = f'curl -X DELETE -w "\n%{{http_version}} %{{http_code}}\n" {server_url}{endpoint}'

    # Exécution de la commande curl
    result = subprocess.run(curl_command, shell=True, capture_output=True, text=True)

    # Extraction du code de statut HTTP et de la ligne d'état
    response_lines = result.stdout.strip().split("\n")
    http_version, status_code = response_lines[-1].split()
    http_status = " ".join(response_lines[-1].split()[2:])

    # Affichage du statut HTTP
    print(f"DELETE {endpoint} - HTTP", status_code)

# Exemple d'utilisation
print("********* test 1 - requête POST sur script cgi *********")
perform_post_request("/cgi-bin/contact.cgi")

print("\n********* test 2 - requête GET sur fichier existant *********")
perform_get_request("/index.html")

print("\n********* test 3 - requête GET sur fichier inexistant *********")
perform_get_request("/unknown_url")

print("\n********* test 4 - requête GET dans une root où la méthode n'est pas autorisée *********")
perform_get_request("/error/about.html")

print("\n********* test 5 - requête DELETE sur fichier existant *********")
upload_file = 'www/upload/test'
if not os.path.exists(upload_file):
    os.makedirs(upload_file)
perform_delete_request("/upload/test")

print("\n********* test 6 - requête DELETE sur fichier inexistant *********")
perform_delete_request("/upload/unknown")
