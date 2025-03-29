#include <stdio.h>
#include <unistd.h>
#include "pcm_c_public.h"

int main()
{
    memdata_t md;
    int test_num_socket = 2, test_num_channel_per_socket = 6;
    bool output = true;

    if (pcm_c_init() != 0) {
        printf("Filed to init  PCM\n");
        return -1;
    }

    pcm_c_start();

    sleep(5);

    pcm_c_get_bandwidth(&md, output);
    for (int socket = 0; socket < test_num_socket; ++socket) {
        printf("=== Socket %d ===\n", socket);
        printf("  Total Read : %.2f MB/s\n", md.iMC_Rd_socket[socket]);
        printf("  Total Write: %.2f MB/s\n", md.iMC_Wr_socket[socket]);

        for (int chan = 0; chan < test_num_channel_per_socket; ++chan) {
            printf("    Channel %d Read : %.2f MB/s\n", chan, md.iMC_Rd_socket_chan[socket][chan]);
            printf("    Channel %d Write: %.2f MB/s\n", chan, md.iMC_Wr_socket_chan[socket][chan]);
        }
    }

    pcm_c_cleanup();

    return 0;
}
