// #include <stdio.h>
// #include "csapp.h"
// /* Recommended max cache and object sizes */
// #define MAX_CACHE_SIZE 1049000
// #define MAX_OBJECT_SIZE 102400
// #define MAXENTRY 100

// int separate_uri(char *uri, char *host, char *port, char *path);
// // void parse_block_file(char *filename, char list[MAXENTRY][MAXLINE], int limit);
// // int blocked_uri(char *uri, char list[MAXENTRY][MAXLINE]);

// int main(int argc, char **argv){
//   int listenfd, connfd;
//   int clientfd;

//   socklen_t clientlen;
//   struct sockaddr_storage clientaddr;

//   rio_t client_rio, server_rio;
//   char c_buf[MAXLINE], s_buf[MAXLINE];
//   ssize_t sn, cn;

//   char method[MAXLINE], uri[MAXLINE], version[MAXLINE];
//   char host[MAXLINE], port[MAXLINE], path[MAXLINE];

//   // char block_list[MAXENTRY][MAXLINE];
//   // int logfd;
//   // char log_buf[MAXLINE];

//   if(argc != 2){
//     fprintf(stderr, "usage: %s <port>\n", argv[0]);
//     fprintf(stderr, "use default port 5000\n");
//     listenfd = Open_listenfd("5000");
//   }else{
//     listenfd = Open_listenfd(argv[1]); //듣기 식별자를 리턴
//   }

//   // logfd = Open("log.list", O_WRONLY | O_APPEND, 0);
//   // memset(block_list, '\0', MAXLINE * MAXENTRY); 
//   // //memset은 어떤 메모리의 시작점부터 연속된 범위를 어떤 값으로(바이트 단위) 모두 지정하고 싶을 때 사용하는 함수이다.
//   // parse_block_file("block.list", block_list, MAXENTRY);
//   while(1){
//     /* wait for connection as a server */
//     clientlen = sizeof(struct sockaddr_storage);
//     connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
//     //Accept 함수는 연결 식별자를 리턴
//     Rio_readinitb(&server_rio, connfd);
//     /*
//      * if uri is full path url like http://localhost:8000/server.c
//      * remove host part http://localhost:8000
//      * only pass /server.c to server
//      */
//     // parse HTTP request first line
//     if(!Rio_readlineb(&server_rio, s_buf, MAXLINE)){
//       //Rio_readlineb는 아무것도 읽지 못할 경우 0을 return 한다.
//       Close(connfd);
//       continue;
//     }

//     sscanf(s_buf, "%s %s %s", method, uri, version);
//     // if(blocked_uri(uri, block_list)){
//     //   printf("%s is blocked\n", uri);
//     //   Close(connfd);
//     //   continue;
//     // }
//     // //log visit
//     // sprintf(log_buf, "visit url: %s\n", uri);
//     // Write(logfd, log_buf, strlen(log_buf));
//     /*write(fd, buf, nbyte)
//       fd: 데이터 전송 영역을 나타내는 파일 디스크립터
//       buf: 전송할 데이터를 가지고 있는 버퍼의 포인터
//       nbyte: 전송할 데이터의 바이트 수
//       ==> 리눅스에서는 파일과 소켓을 동일하게 취급하므로 소켓을 통해서 
//       다른 호스트에게 데이터를 전송 할 때에도 write() 함수를 사용한다.
//     */
//     memset(host, '\0', MAXLINE);
//     memset(port, '\0', MAXLINE);
//     memset(path, '\0', MAXLINE);
//     int res;
//     //separate_uri의 error를 파악해야함
//     if((res = separate_uri(uri, host, port, path)) == -1){
//       fprintf(stderr, "not http protocol\n");
//       Close(connfd);
//       continue;
//     }else if (res == 0){
//       fprintf(stderr, "not a abslute request path\n");
//       Close(connfd);
//       continue;
//     }
//     // connect server as a client
//     clientfd = Open_clientfd(host, port);
//     Rio_readinitb(&client_rio, clientfd);
//     /*
//      *  browser  -->  proxy  -->  server
//      *
//      *  send requests
//      */
//     // write first request line
//     sprintf(s_buf, "%s %s %s\n", method, path, version);
//     Rio_writen(clientfd, s_buf, strlen(s_buf));
//     printf("%s", s_buf);
//     do{
//       // pass next http requests
//       sn = Rio_readlineb(&server_rio, s_buf, MAXLINE);
//       printf("%s", s_buf);
//     } while(strcmp(s_buf, "\r\n"));
//     /*
//      *  server  -->  proxy  -->  browser
//      *
//      *  server send response back
//      */
//     while((cn = Rio_readlineb(&client_rio, c_buf, MAXLINE)) != 0)
//       Rio_writen(connfd, c_buf, cn);
//     Close(connfd);
//     Close(clientfd);
//   }

//   // Close(logfd);
// }

// /*
//  * if uri is abslute path url like
//  *   http://localhost:8888/something
//  *   or
//  *   http://localhost/something (port default is 80)
//  * separate into three part and return 1
//  *
//  * if uri is relative path like /something
//  * do nothing and return 0
//  *
//  * if uri is abslute path and not http protocal like https/ftp/etc
//  * do nothing, return -1, it's error
//  */
// int separate_uri(char *uri, char *host, char *port, char *path){
//   // relative path
//   if (uri[0] == '/')
//     return 0;

//   //abslute path
//   char *prefix = "http://";
//   int prelen = strlen(prefix);
//   // if not http protocal, error
//   if (strncmp(uri, prefix, prelen) != 0)
//     return -1;
  
//   char *start, *end;
//   start = uri + prelen;
//   end = start;
//   //copy host
//   while( *end != ':' && *end != '/'){
//     end++;
//   }
//   strncpy(host, start, end-start);
  
//   //port is provided
//   if(*end == ':'){
//     //skil ':'
//     ++end;
//     start = end;
//     //copy port
//     while(*end != '/'){
//       end++;
//     }
//     strncpy(port, start, end-start);
//   }else{
//     strncpy(port, "80", 2);
//   }
//   // copy path
//   strcpy(path, end);
// }

#include <stdio.h>
#include "csapp.h"
/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400
#define LRU_MAGIC_NUMBER 9999
#define CACHE_OBJS_COUNT 10
/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";
static const char *conn_hdr = "Connection: close\r\n";
static const char *prox_hdr = "Proxy-Connection: close\r\n";
static const char *host_hdr_format = "Host: %s\r\n";
static const char *requestlint_hdr_format = "GET %s HTTP/1.0\r\n";
static const char *endof_hdr = "\r\n";

static const char *connection_key = "Connection";
static const char *user_agent_key= "User-Agent";
static const char *proxy_connection_key = "Proxy-Connection";
static const char *host_key = "Host";
void *thread(void *vargp);

void doit(int connfd);
void parse_uri(char *uri,char *hostname,char *path,int *port);
void build_http_header(char *http_header,char *hostname,char *path,int port,rio_t *client_rio);
int connect_endServer(char *hostname,int port,char *http_header);
/*cache function*/
void cache_init();
int cache_find(char *url);
int cache_eviction();
void cache_LRU(int index);
void cache_uri(char *uri,char *buf);
void readerPre(int i);
void readerAfter(int i);

typedef struct {
    char cache_obj[MAX_OBJECT_SIZE];
    char cache_url[MAXLINE];
    int LRU;
    int isEmpty;

    int readCnt;            /*count of readers*/
    sem_t wmutex;           /*protects accesses to cache*/
    sem_t rdcntmutex;       /*protects accesses to readcnt*/

}cache_block;

typedef struct {
    cache_block cacheobjs[CACHE_OBJS_COUNT];  /*ten cache blocks*/
    int cache_num;
}Cache;

Cache cache;

int main(int argc, char **argv){
    int listenfd, connfd;
    socklen_t clientlen;
    char hostname[MAXLINE], port[MAXLINE];
    pthread_t tid;
    struct sockaddr_storage clientaddr;

    cache_init();
    if(argc != 2){
        fprintf(stderr,"usage :%s <port> \n",argv[0]);
        exit(1);
    }

    Signal(SIGPIPE, SIG_IGN);
    //sigpipe 무시 => 파이프가 끊겼음을 무시
    listenfd = Open_listenfd(argv[1]);
    while(1){
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

        //소켓 주소 구조체를 대응되는 호스트와 서비스이름 스트링으로 변환
        Getnameinfo((SA*)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
        printf("Accepted connection from (%s %s).\n",hostname,port);
        /*concurrent request*/
        Pthread_create(&tid,NULL,thread,(void *)connfd);
        /*pthread_create: 쓰레드를 생성
            첫번째 매개변수: 쓰레드가 성공적으로 생성되었을 때 생성된 쓰레드를 식별하기 위해 사용되는 쓰레드 식별자
            두번째 매개변수: 쓰레드 특성을 지정하기 위해서 사용하며, null일 경우 기본 쓰레드 특성을 이용
            세번째 매개변수: 분기시켜서 실행할 쓰레드 함수
            네번째 매개변수: 위의 분기되 쓰레드 함수에서 사용되는 매개변수
        */
    }
    return 0;
}
/* thread function */
void *thread(void *vargp){
    int connfd = (int) vargp;
    Pthread_detach(pthread_self());
    //pthread_self: 현재 쓰레드의 식별자 리턴
    //pthread_detach: 특정 쓰레드를 분리시킨다.
    doit(connfd);
    Close(connfd);
}

/* handle the client HTTP transaction */
void doit(int connfd){
    int end_serverfd; // end_server file discriptor
    
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char endserver_http_header[MAXLINE];

    /*store the request line arguments*/
    char hostname[MAXLINE], path[MAXLINE];
    int port;    
    rio_t client_rio, server_rio;/*rio is client's rio,server_rio is endserver's rio*/

    Rio_readinitb(&client_rio, connfd);
    Rio_readlineb(&client_rio, buf, MAXLINE);
    sscanf(buf, "%s %s %s", method, uri, version); /*read the client request line*/

    char url_store[100];
    strcpy(url_store, uri);
    if(strcasecmp(method, "GET")){
        printf("Proxy does not implement the method");
        return;
    }

    /* uri is cached? */
    int cache_index;
    if((cache_index = cache_find(url_store)) != -1){
        //cache_find == -1: url이 cache에 저장되어 있지 않음
        readerPre(cache_index);
        Rio_writen(connfd, cache.cacheobjs[cache_index].cache_obj, strlen(cache.cacheobjs[cache_index].cache_obj));
        readerAfter(cache_index);
        return;
    }
    // uri를 나눠서 얻은 정보를 hostname, path, port에 담는다.
    parse_uri(uri, hostname, path, &port);
    /* build the http header which will send to the end server */
    build_http_header(endserver_http_header, hostname, path, port, &client_rio);
    // end server에 연결
    end_serverfd = connect_endServer(hostname, port, endserver_http_header);
    if(end_serverfd < 0){
        printf("conection failed\n");
        return;
    }

    Rio_readinitb(&server_rio, end_serverfd);
    Rio_writen(end_serverfd, endserver_http_header, strlen(endserver_http_header));

    /*end server로부터 message를 받고 client에게 보낸다.*/
    char cachebuf[MAX_OBJECT_SIZE];
    int sizebuf = 0;
    size_t n;
    while((n = rio_readlineb(&server_rio, buf, MAXLINE)) != 0){
        sizebuf += n;
        if(sizebuf < MAX_OBJECT_SIZE){
            strcat(cachebuf, buf);
        }
        Rio_writen(connfd, buf, n);
    }
    Close(end_serverfd);

    /* store it*/
    if(sizebuf < MAX_OBJECT_SIZE){
        cache_uri(url_store, cachebuf);
    }
} 


void build_http_header(char *http_header, char *hostname, char *path, int port, rio_t *client_rio){
    char buf[MAXLINE], request_hdr[MAXLINE], other_hdr[MAXLINE], host_hdr[MAXLINE];
    // request line
    sprintf(request_hdr, requestlint_hdr_format, path); // GET {path} HTTP/1.0
    /*get other request header for client rio and change it*/
    while(Rio_readlineb(client_rio, buf, MAXLINE) > 0 ){
        if(strcmp(buf, endof_hdr) == 0) // buf == "\r\n"이면 0
            break;
        if(!strncasecmp(buf, host_key, strlen(host_key))){ /*Host:*/
            strcpy(host_hdr, buf);
            continue;
        }
        if(strncasecmp(buf,connection_key,strlen(connection_key))
            &&strncasecmp(buf,proxy_connection_key,strlen(proxy_connection_key))
            &&strncasecmp(buf,user_agent_key,strlen(user_agent_key)))
        {
            /*
            buf = "Connection" or "User-Agent" or "Proxy-Connection";
            */
            strcat(other_hdr,buf);
        }
    }
    if(strlen(host_hdr) == 0){
        sprintf(host_hdr, host_hdr_format, hostname);
    }
    sprintf(http_header, "%s%s%s%s%s%s%s", 
            request_hdr, 
            host_hdr,
            conn_hdr,
            prox_hdr,
            user_agent_hdr,
            other_hdr,
            endof_hdr);
    return;
}

/*connect to the end server*/
inline int connect_endServer(char *hostname, int port, char *http_header){
    char portStr[100];
    sprintf(portStr, "%d", port);
    //client로써 end server에 접근
    return Open_clientfd(hostname, portStr);
}

/*parse the uri to get hostname,file path ,port*/
void parse_uri(char *uri,char *hostname,char *path,int *port)
{
    *port = 80;
    char* pos = strstr(uri,"//");

    pos = pos!=NULL? pos+2:uri;

    char*pos2 = strstr(pos,":");
    if(pos2!=NULL)
    {
        *pos2 = '\0';
        sscanf(pos,"%s",hostname);
        sscanf(pos2+1,"%d%s",port,path);
    }
    else
    {
        pos2 = strstr(pos,"/");
        if(pos2!=NULL)
        {
            *pos2 = '\0';
            sscanf(pos,"%s",hostname);
            *pos2 = '/';
            sscanf(pos2,"%s",path);
        }
        else
        {
            sscanf(pos,"%s",hostname);
        }
    }
    return;
}

/**************************************
 * Cache Function
 **************************************/

void cache_init(){
    cache.cache_num = 0;
    int i;
    for(i = 0; i<CACHE_OBJS_COUNT;i++){ //10개의 빈 cache 생성
        cache.cacheobjs[i].LRU = 0;
        cache.cacheobjs[i].isEmpty = 1;
        /*프로세스간 특정 data를 공유하게 될 경우 발생하는 문제를 막기위해
        * 한번에 하나의 프로세스만 접근 가능하도록 만들어주어야하고
        * 이를 위해 세마포어를 사용한다.
        */
        Sem_init(&cache.cacheobjs[i].wmutex, 0, 1);
        Sem_init(&cache.cacheobjs[i].rdcntmutex,0,1);
        /* sem_init(sem_t *sem, int pshared, unsigned int value);
        * *sem: 초기화할 세마포어의 포인터를 넣는 위치
        * pshared: 0인 경우 세마포어는 프로세스 안에서의 쓰레드들끼리 공유, 그 외에는 프로세스 간 공유
        * value: 세마포어 초기 값
        */
       cache.cacheobjs[i].readCnt = 0;
    }
}

void readerPre(int i){
    P(&cache.cacheobjs[i].rdcntmutex);
    //sem_wait: 세마포어 값 감소 함수, 초기값이 1일때 세마포어 값을 0으로,
    cache.cacheobjs[i].readCnt++;
    if(cache.cacheobjs[i].readCnt == 1){
        P(&cache.cacheobjs[i].wmutex);
    }
    V(&cache.cacheobjs[i].rdcntmutex);
    //sem_post: 세마포어 값을 1 증가 시킨다.
}

void readerAfter(int i){
    P(&cache.cacheobjs[i].rdcntmutex);
    cache.cacheobjs[i].readCnt--;
    if(cache.cacheobjs[i].readCnt==0){
        V(&cache.cacheobjs[i].wmutex);
    }
    V(&cache.cacheobjs[i].rdcntmutex);
}

void writePre(int i){
    P(&cache.cacheobjs[i].wmutex);
}

void writeAfter(int i){
    V(&cache.cacheobjs[i].wmutex);
}

/* find url is in the cache or not*/
int cache_find(char *url){
    int i;
    for(i=0; i<CACHE_OBJS_COUNT; i++){
        readerPre(i);
        if((cache.cacheobjs[i].isEmpty==0) && (strcmp(url, cache.cacheobjs[i].cache_url) == 0)){
            break;
        }
        readerAfter(i);
    }
    if(i>=CACHE_OBJS_COUNT)
        return -1;
    return i;
}

/* find the empty cacheObj or which cacheObj should be evictioned */
int cache_eviction(){
    int min = LRU_MAGIC_NUMBER;
    int minindex = 0;
    int i;
    for(i=0; i<CACHE_OBJS_COUNT; i++){
        readerPre(i);
        if(cache.cacheobjs[i].isEmpty == 1){//choose if cache block empty
            minindex = i;
            readerAfter(i);
            break;
        }
        if(cache.cacheobjs[i].LRU < min){//if not empty choose the min LRU
            minindex = i;
            readerAfter(i);
            min = cache.cacheobjs[i].LRU;
            continue;
        }
        readerAfter(i);
    }
    return minindex;
}

/* update the LRU number except the new cache one */
void cache_LRU(int index){
    int i;
    for(i=0; i<index; i++){
        writePre(i);
        if(cache.cacheobjs[i].isEmpty == 0){
            cache.cacheobjs[i].LRU--;
        }
        writeAfter(i);
    }
    i++;
    for(i; i<CACHE_OBJS_COUNT; i++){
        writePre(i);
        if(cache.cacheobjs[i].isEmpty == 0){
            cache.cacheobjs[i].LRU--;
        }
        writeAfter(i);
    }
}
/*cache the uri and content*/
void cache_uri(char *uri, char *buf){
    int i = cache_eviction();
    writePre(i);
    strcpy(cache.cacheobjs[i].cache_obj, buf);
    strcpy(cache.cacheobjs[i].cache_url, uri);
    cache.cacheobjs[i].isEmpty = 0;
    cache.cacheobjs[i].LRU = LRU_MAGIC_NUMBER;
    cache_LRU(i);
    writeAfter(i);
}