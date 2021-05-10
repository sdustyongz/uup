#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>

int  inet4_pton(int family,const char *strptr,void *addrptr){
    if(family==AF_INET){
        struct in_addr in_val;
        if(inet_aton(strptr,&in_val)){
            memcpy(addrptr,&in_val,sizeof(struct in_addr));
            return 1;
        }
        return 0;
    }

    errno=EAFNOSUPPORT;
    return -1;
}


char * inet4_ntop(int family,void * addrptr,char * strptr,int len){
    if(family==AF_INET){
        char *ip=inet_ntoa(*(struct in_addr *)addrptr);
        memcpy(strptr,ip,len);
        return strptr;
    }
    return NULL;
}





int main(int ac,char *av[]){
    if(ac<2){
        printf("useage error\n");
        return -1;
    }
    char ip[INET_ADDRSTRLEN];
    struct in_addr addr;
    inet4_pton(AF_INET,av[1],&addr);
    printf("ip int is %xd\n",addr.s_addr);
    char nip[INET_ADDRSTRLEN];
    char * nn=inet4_ntop(AF_INET,&addr,nip,INET_ADDRSTRLEN);
    printf("return is %s , parameter return is %s\n",nn,nip);
}
