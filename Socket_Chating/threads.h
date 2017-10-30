#pragma once

/**
 *   receive_thread is used for receive the msg from other user.
 *   @param  dummy   the client socket for this thread.
 */
void receive_thread(void* dummy);