#include <fcgiapp.h>
#include <stdio.h>

int main() {
  FCGX_Init();
  int sockfd = FCGX_OpenSocket("127.0.0.1:9000", 100);

  FCGX_Request req;
  FCGX_InitRequest(&req, sockfd, 0);

  while (FCGX_Accept_r(&req) >= 0) {
    FCGX_FPrintF(req.out, "Content-Type: text/html\n\n");
    FCGX_FPrintF(req.out, "Hello world!");
    FCGX_Finish_r(&req);
  }
}