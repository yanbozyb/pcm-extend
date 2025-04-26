#include <stdio.h>
#include <unistd.h>
#include "pcm_c_public.h"

int main()
{
    memdata_t md;
    core_metrics_t core_metrics;
    int test_num_socket = 2, test_num_channel_per_socket = 6;
    int num_cores;
    bool output = true;

    if (pcm_c_init() != 0) {
        printf("Filed to init  PCM\n");
        return -1;
    }

    num_cores = pcm_c_get_num_cores();
    pcm_c_start();

    sleep(5);

    pcm_c_get_metrics(&md, &core_metrics, output);
    for (int socket = 0; socket < test_num_socket; ++socket) {
        printf("=== Socket %d ===\n", socket);
        printf("  Total Read : %.2f MB/s\n", md.iMC_Rd_socket[socket]);
        printf("  Total Write: %.2f MB/s\n", md.iMC_Wr_socket[socket]);

        for (int chan = 0; chan < test_num_channel_per_socket; ++chan) {
            printf("    Channel %d Read : %.2f MB/s\n", chan, md.iMC_Rd_socket_chan[socket][chan]);
            printf("    Channel %d Write: %.2f MB/s\n", chan, md.iMC_Wr_socket_chan[socket][chan]);
        }
    }

    printf("=== Core Outputs ===\n");
    for (int core = 0; core < num_cores; core++) {
        printf("Core %d: Local %llu MB/s, Remote: %llu MB/s\n", 
            core, core_metrics.core_local_bw[core], core_metrics.core_remote_bw[core]);
    }

    pcm_c_cleanup();

    return 0;
}
