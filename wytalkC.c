/*
 * wytalkC.c
 * Author : Cole Sigmon
 * Date : April 11, 2023
 *
 * COSC 3750, Homework 6
 *
 * This is wytalkC.c it is the "Client" of this program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "socketfun.h"

#define PORT 51100
#define BUFF_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        perror("Not Enough Arguments");
        return -1;
    }

    int sockfd, len;
    char buffer[BUFF_SIZE];

    sockfd = request_connection(argv[1], PORT);
    if (sockfd < 0)
    {
        perror("Server Connection Failure");
        return -1;
    }

    while (1)
    {
        if (fgets(buffer, BUFF_SIZE, stdin) == NULL)
        {
            if (feof(stdin)) // Keyboard input stops
            {
                break;
            }
            else
            {
                perror("'Client' Keyboard Read Failure");
                return -1;
            }
        }

        len = write(sockfd, buffer, strlen(buffer));
        if (len <= 0)
        {
            perror("'Client' Socket Write Failure");
            return -1;
        }

        len = read(sockfd, buffer, BUFF_SIZE);
        if (len <= 0)
        {
            perror("'Client' Socket Read Failure");
            return -1;
        }
        buffer[len] = '\0';
    }

    close(sockfd);

    return 0;
}
