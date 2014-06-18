#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>

#define DEBUG_ENABLED

#include "libirecovery.h"
#include "sn0wbreak.h"

int main(int argc, char **argv)
{
    irecv_init();
    irecv_client_t client = NULL;
    if (irecv_open_with_ecid_and_attempts(&client, 0, 5) != IRECV_E_SUCCESS)
    {
        ERROR("Could not connect to iDevice! Make sure you are in DFU mode...\n");
        return -1;
    }

    irecv_device_t device = NULL;
    if (irecv_devices_get_device_by_client(client, &device) != IRECV_E_SUCCESS)
    {
        ERROR("Something went wrong, could not get device!\n");
        return -1;
    }
    DEBUG("Connected to %s (Model: %s, Board ID: 0x%02x, Chip ID: 0x%04x)\n", device->product_type, device->hardware_model, device->board_id, device->chip_id);

    const struct irecv_device_info *info = irecv_get_device_info(client);
    if (!info)
    {
        ERROR("Could not get iDevice info!\n");
        return -1;
    }
    DEBUG("ECID: %"PRId64" (decimal), %"PRIX64" (hexadecimal)\n", info->ecid, info->ecid);
    DEBUG("IMEI: %s\n", info->imei);

    INFO("Successfully connected to device!\n");
    return 0;
}
