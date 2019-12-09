#ifndef TINYPROXY_IP_TOOLS_H
#define TINYPROXY_IP_TOOLS_H

#include "ip-tools.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

int parse_ipv6(char *buf, char *prefix, char *hostmask) {
    int i = 0;
    char *p = strtok (buf, "/");
    char *array[3];

    while (p != NULL)
    {
        array[i++] = p;
        p = strtok (NULL, "/");
    }

    sprintf(prefix, "%s", array[0]);
    sprintf(hostmask, "%s", array[1]);

    return 0;
}

int get_ipv6_for_subnet(char input, char *result) {
    const char *p;

    unsigned char address[16];
    char saddress[100];
    int rc, fd;

    char sprefix[100];
    char hostmax[4];

    parse_ipv6(input, sprefix, hostmax);
    int hostMaxInt = atoi(hostmax);
    int randomFrom = hostMaxInt / 8;

    printf("Prefix is: %s, hostmask is %s (%d) \n", sprefix, hostmax, hostMaxInt);

    fd = open("/dev/urandom", O_RDONLY);
    if(fd < 0) {
        perror("open(random)");
        exit(1);
    }

    rc = inet_pton(AF_INET6, sprefix, address);
    if(rc != 1) {
        perror("inet_pton");
        exit(1);
    }

    printf("%s", "harom");
    rc = read(fd, address + randomFrom, 16 - randomFrom);
    if(rc != 16 - randomFrom) {
        perror("read(random)");
        exit(1);
    }

    address[randomFrom] &= ~3;

    if(fd >= 0)
        close(fd);

    p = inet_ntop(AF_INET6, address, saddress, 100);
    if(p == NULL) {
        perror("inet_ntop");
        exit(1);
    }
    printf("kek 3");
    sprintf(result, "%s", p);
    printf("Kek 2");
    return 0;
}


#endif
