#include <arpa/inet.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


uint8_t checksum(unsigned char* bytes, size_t size) {
    uint8_t result = 0;
    for (size_t i = 0; i < size; ++i) {
        result = (result + bytes[i]) % 256;
    }
    return result;
}

void generateBytes(unsigned char* bytes, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        bytes[i] = rand() % 256; 
    }
}

int clientRoutine(uint16_t port, size_t message_size, size_t cycles) {
    size_t success = 0;
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    inet_aton("127.0.0.1", &(addr.sin_addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    int cnct = connect(sock,
        (struct sockaddr*)&addr,
        sizeof(addr));
    if (cnct < 0) {
        perror("Connect");
        goto end;
    }
    for (size_t i = 0; i < cycles; ++i) {
        unsigned char message[message_size];
        generateBytes(message, message_size);

        int wr = write(sock, message, message_size);
        if (wr < 0) {
            perror("write");
            goto end;
        }

        uint8_t correct_checksum = checksum(message, message_size);
        uint8_t server_answer = 0;

        int rd = read(sock, &server_answer, sizeof(server_answer));
        if (rd != sizeof(server_answer)) {
            perror("read");
            goto end;
        }

        if (server_answer == correct_checksum) {
            ++success;
        } else {
            fprintf(stderr, "%s\n", "Answer is incorrect!");
        }
    }
    
end:
    shutdown(sock, SHUT_RDWR);
    close(sock);

    return (success == cycles);
}

int autoClientRoutine() {
    size_t message_size = 20;
    uint16_t port = 1234;

    return clientRoutine(port, message_size, 20);
}

int main(int argc, char** argv) {
    size_t cycles = 5;
    if (argc == 2) {
        cycles = atoi(argv[1]);
    }
    size_t successful = 0;

    for (size_t i = 0; i < cycles; ++i) {
        if (autoClientRoutine()) {
            ++successful;
        }
    }

    printf("%zu connections where successful out of %zu (%.2lf%%)\n", 
        successful, 
        cycles, 
        100.0*successful/cycles);
}