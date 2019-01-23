#include <stdio.h>
#include <stdint.h>
#include "messend.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>


int main(int argc, char **argv) {

    messend_startup();

    Acceptor* acceptor = acceptor_create(9001);

    struct Peer* peer = 0;
    
    while(!peer) {
        printf("loopy\n");
        //peer = messend_accept(9001);
        peer = acceptor_accept(acceptor);
        SDL_Delay(100);
    }

    struct Message message;
    message.data = "Hi from server";
    message.size = 14;
    peer_send_message(peer, message);

    struct Message* recvMessage = peer_receive_message(peer);

    for (int i = 0; i < recvMessage->size; i++) {
        printf("%c", ((uint8_t*)(recvMessage->data))[i]);
    }
    printf("\n");

    message_free(recvMessage);

    peer_free(peer);
    peer = 0;

    messend_shutdown();

    return 0;
}
