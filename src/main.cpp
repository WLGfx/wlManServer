#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void exit_handler() {
    puts("Server stopped...\n");
}

int main(int argc, char *argv[]) {
    atexit(exit_handler);

    // yuk, getting instantly replaced after initial commit
    int result = system("curl --head --silent --fail http://localhost:8080");

    if (result != 0) {
        puts("Server started...\n");
    } else {
        puts("Server couldn't start...\n");
    }
    return 0;
}
