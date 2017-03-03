/*
 * Copyright 2014 Vlad V. Ungureanu <ungureanuvladvictor@gmail.com>.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this Github repository and wiki except in
 * compliance with the License. You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <stdio.h>
#include "libusb.h"
#include "utils.h"

static void print_devs(libusb_device **devs)
{
	libusb_device *dev;
	int i = 0, j = 0;
	uint8_t path[8]; 

	while ((dev = devs[i++]) != NULL) {
		struct libusb_device_descriptor desc;
		int r = libusb_get_device_descriptor(dev, &desc);
		if (r < 0) {
			fprintf(stderr, "failed to get device descriptor");
			return;
		}

		printf("%04x:%04x (bus %d, device %d)",
			desc.idVendor, desc.idProduct,
			libusb_get_bus_number(dev), libusb_get_device_address(dev));

		r = libusb_get_port_numbers(dev, path, sizeof(path));
		if (r > 0) {
			printf(" path: %d", path[0]);
			for (j = 1; j < r; j++)
				printf(".%d", path[j]);
		}
		printf("\n");
	}
}

int main(int argc, const char * argv[]) 
{
	int actual;
	int result;
	int r;

#if 0 /// TODO
	ssize_t fullSize = sizeof(bootp_packet) + sizeof(udp_t) +
			   sizeof(struct iphdr) + sizeof(struct ethhdr) +
			   sizeof(rndis_hdr);
	ssize_t rndisSize = sizeof(rndis_hdr);
	ssize_t etherSize = sizeof(struct ethhdr);
	ssize_t arpSize = sizeof(arp_hdr);
	ssize_t ipSize = sizeof(struct iphdr);
	ssize_t udpSize = sizeof(udp_t);
	ssize_t bootpSize = sizeof(bootp_packet);
	ssize_t tftpSize = sizeof(tftp_data);

#endif
	unsigned char *data = (unsigned char*)calloc(1, 1000);
	unsigned char *buffer = (unsigned char*)malloc(450 *
				sizeof(unsigned char));

	FILE *send;


	libusb_device **devs = NULL;
	libusb_device_handle *dev_handle = NULL;
	libusb_context *ctx = NULL;

	ssize_t cnt;

	r = libusb_init(&ctx);
	if (r < 0) {
		printf("Init error!\n");
		exit(1);
	}
	libusb_set_debug(ctx, 3);
	
	while (dev_handle == NULL) {
		r = libusb_get_device_list(ctx, &devs);
		if (r < 0) {
			printf("Cannot get device list.\n");
			print_devs(devs);
		}
		else {
			print_devs(devs);
		}
		dev_handle = libusb_open_device_with_vid_pid(ctx, ROMVID, ROMPID);
		libusb_free_device_list(devs, 1);
	}

	if (libusb_kernel_driver_active(dev_handle, 0) == 1) {
		libusb_detach_kernel_driver(dev_handle, 0);
	}

	r = libusb_claim_interface(dev_handle, 1);
	if (r < 0) {
		printf("Cannot Claim Interface!\n");
		exit(1);
	}

	r = libusb_bulk_transfer(dev_handle, (129 | LIBUSB_ENDPOINT_IN),
				 buffer, 450, &actual, 0);


	libusb_exit(ctx);
	return 0;
}
