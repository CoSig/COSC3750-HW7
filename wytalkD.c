/*
 * wytalkD.c
 * Author : Cole Sigmon
 * Date : April 11, 2023
 *
 * COSC 3750, Homework 6
 *
 * This is wytalkD.c it is the "Daemon" of this program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "socketfun.h"

#define PORT 51100
#define BUFF_SIZE 1024

int main()
{
    int sockfd, connfd, len;
    char buffer[BUFF_SIZE];

    sockfd = serve_socket(NULL, PORT);
    if (sockfd < 0)
    {
        perror("Open Socket Failure");
        return -1;
    }

    connfd = accept_connection(sockfd);
    if (connfd < 0)
    {
        perror("Accept Connection Failure");
        return -1;
    }

    while (true)
    {
        len = read(connfd, buffer, BUFF_SIZE);

        if (len <= 0)
        {
            perror("'Daemon' Socket Read Failure");
            return -1;
        }

        buffer[len] = '\0';

        if (fgets(buffer, BUFF_SIZE, stdin) == NULL)
        {
            if (feof(stdin)) // Keyboard input stops
            {
                break;
            }
            else
            {
                perror("'Daemon' Keyboard Read Failure");
                return -1;
            }
        }

        len = write(connfd, buffer, strlen(buffer));
        if (len <= 0)
        {
            perror("'Daemon' Socket Write Failure");
            return -1;
        }
    }

    close(connfd);
    close(sockfd);

    return 0;
}