#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void resolve_domain_name(char input[]) {
  struct hostent *host;

  printf("Domain: %s\n", input);
  host = gethostbyname(input);

  if (host == NULL) {
    printf("Information not found\n");
    return;
  }

  printf("Offcial IP: %s \n", inet_ntoa(*((struct in_addr *)host->h_addr)));

  char **aliasIP = host->h_aliases;

  printf("Alias IP:\n ");

  while (*aliasIP != NULL) {
    printf("%s\n",inet_ntoa(*((struct in_addr *)aliasIP)));
    aliasIP++;
  }
}

void resolve_ip_addr(char input[]) {
  struct hostent *host;
  struct in_addr addr;

  printf("IP address: %s\n", input);
  addr.s_addr = inet_addr(input);
  if (addr.s_addr == INADDR_NONE) {
    printf("Information not found\n");
    return;
  } else
    host = gethostbyaddr((char *) &addr, 4, AF_INET);

  if (host == NULL) {
    printf("Information not found\n");
    return;
  }

  printf("Offcial name: %s \n", host->h_name);

  char **AliasAddr = host->h_aliases;

  printf("Alias name:\n");

  while ( *AliasAddr != NULL) {
    printf("%s\n", *AliasAddr);
    AliasAddr++;
  }
}

int main(int argc, char const *argv[]) {
  char input[30];

  if (argc != 2) {
    printf("Syntax is incorrect!\n");
    return 0;
  }

  strcpy(input, argv[1]);

  if (isalpha(input[0])) {        
    resolve_domain_name(input);
  } else {
    resolve_ip_addr(input);       
  }

  // while (host->h_aliases[i] != 0) {
  //   addr.s_addr = *(u_long *) host->h_aliases[i++];
  //   printf("\tIPv4 Address #%d: %s\n", i, inet_ntoa(addr));
  // }
  return 0;
}