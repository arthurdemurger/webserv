#include <iostream>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <vector>

int main ()
{
    // Création du socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Erreur lors de la création du socket" << std::endl;
        return 0;
    }

    // Configuration de l'adresse et du port
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(8080); // Utilisez le port de votre choix

    // Liaison du socket à l'adresse et au port
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Erreur lors de la liaison du socket" << std::endl;
        close(serverSocket);
        return 0;
    }

    // Mise en écoute du socket
    if (listen(serverSocket, 10) == -1) {
        std::cerr << "Erreur lors de la mise en écoute du socket" << std::endl;
        close(serverSocket);
        return 0;
    }

    // Création d'un ensemble de sockets à surveiller
    fd_set readSet, writeSet;
    FD_ZERO(&readSet);
    FD_ZERO(&writeSet);
    FD_SET(serverSocket, &readSet);
    int maxSocket = serverSocket;

    std::vector<int> clientSockets;

    while (true) {
        // Copie des ensembles de sockets pour la fonction select()
        fd_set tmpReadSet = readSet;
        fd_set tmpWriteSet = writeSet;

        // Appel à select() pour attendre les activités sur les sockets
        if (select(maxSocket + 1, &tmpReadSet, &tmpWriteSet, nullptr, nullptr) == -1) {
            std::cerr << "Erreur lors de l'appel à select()" << std::endl;
            close(serverSocket);
            return 0;
        }

        // Vérification de l'activité sur le socket principal (nouvelle connexion)
        if (FD_ISSET(serverSocket, &tmpReadSet))
		{
            int clientSocket = accept(serverSocket, nullptr, nullptr);
            if (clientSocket == -1) {
                std::cerr << "Erreur lors de l'acceptation de la connexion client" << std::endl;
                close(serverSocket);
                return 0;
            }

            // Ajout du socket client à l'ensemble de sockets en lecture
            FD_SET(clientSocket, &readSet);

            // Ajout du socket client à l'ensemble de sockets en écriture
            FD_SET(clientSocket, &writeSet);

            // Mise à jour du maximum de socket
            if (clientSocket > maxSocket)
                maxSocket = clientSocket;

            // Ajout du socket client à la liste des sockets clients
            clientSockets.push_back(clientSocket);
        }

        // Vérification de l'activité sur les autres sockets (lecture ou écriture)
        for (int i = 0; i < clientSockets.size(); ++i) {
            int clientSocket = clientSockets[i];

            if (FD_ISSET(clientSocket, &tmpReadSet)) {
                char buffer[1024];
                memset(buffer, 0, sizeof(buffer));

                // Lecture des données du socket
                ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));
                if (bytesRead == -1) {
                    std::cerr << "Erreur lors de la lecture des données du socket" << std::endl;
                    close(serverSocket);
                    return 0;
                }

                if (bytesRead == 0)
				{
                    // Le client a fermé la connexion
                    close(clientSocket);

                    // Retrait du socket client des ensembles de sockets
                    FD_CLR(clientSocket, &readSet);
                    FD_CLR(clientSocket, &writeSet);

                    // Suppression du socket client de la liste des sockets clients
                    clientSockets.erase(clientSockets.begin() + i);

                    --i;  // Réduire l'indice pour compenser la suppression d'élément
                }
				else
				{
                    // Traitez les données reçues et formulez la réponse HTTP appropriée

                    // Exemple simple de réponse HTTP
                    std::string response = "HTTP/1.1 200 OK\r\n"
                                           "Content-Length: 13\r\n"
                                           "Content-Type: text/plain\r\n"
                                           "\r\n"
                                           "Hello, World!";

                    // Ajout du socket client à l'ensemble de sockets en écriture
                    FD_SET(clientSocket, &writeSet);
                }
            }

            if (FD_ISSET(clientSocket, &tmpWriteSet)) {
                // Envoi de la réponse au client
                std::string response = "HTTP/1.1 200 OK\r\n"
                                       "Content-Length: 13\r\n"
                                       "Content-Type: text/plain\r\n"
                                       "\r\n"
                                       "Hello, World!";

                ssize_t bytesSent = send(clientSocket, response.c_str(), response.length(), 0);
                if (bytesSent == -1) {
                    std::cerr << "Erreur lors de l'envoi de la réponse au client" << std::endl;
                    close(serverSocket);
                    return 0;
                }

                // Fermeture du socket client après la réponse
                close(clientSocket);

                // Retrait du socket client des ensembles de sockets
                FD_CLR(clientSocket, &readSet);
                FD_CLR(clientSocket, &writeSet);

                // Suppression du socket client de la liste des sockets clients
                clientSockets.erase(clientSockets.begin() + i);

                --i;  // Réduire l'indice pour compenser la suppression d'élément
            }
        }
    }

    // Fermeture du socket principal
    close(serverSocket);
}
