#pragma once
/**
*   send_thread is used for send the msg to other user.
*   @param  dummy   use for starting this thread, it is the socket about the other user.
*/
void send_thread(void* dummy);

/**
*   receive_thread is used for receive the msg from other user.
*   @param  dummy   use for starting this thread, it is the socket about the other user.
*/
void receive_thread(void* dummy);