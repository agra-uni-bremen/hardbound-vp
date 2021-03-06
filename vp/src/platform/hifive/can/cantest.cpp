/*
 * Copyright (c) 2017-2018 Group of Computer Architecture, University of Bremen <riscv@systemc-verification.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * cantest.cpp
 *
 *  Created on: 22 Mar 2019
 *      Author: dwd
 */
#include <linux/can.h>
#include <linux/can/raw.h>
#include <cstring>
#include <iostream>

#include <endian.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {
	int s;
	struct sockaddr_can addr;
	struct ifreq ifr;

	s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (s < 0) {
		perror("Could not open socket!");
	}

	memset(&ifr, 0, sizeof(struct ifreq));
	strcpy(ifr.ifr_name, "slcan0");
	if (ioctl(s, SIOCGIFINDEX, &ifr) < 0) {
		perror("Could not ctl to device");
	}

	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("Could not bind to can family");
	}

	// while(true)
	{
		struct can_frame frame;

		int nbytes = read(s, &frame, sizeof(struct can_frame));

		if (nbytes < 0) {
			perror("can raw socket read");
			return 1;
		}

		/* paranoid check ... */
		if (nbytes < sizeof(struct can_frame)) {
			fprintf(stderr, "read: incomplete CAN frame\n");
			return 1;
		}

		/* do something with the received CAN frame */

		cout << "received id " << frame.can_id << " len " << unsigned(frame.can_dlc) << endl;

		for (uint8_t i = 0; i < frame.can_dlc; i++) {
			printf("%s%02X", i > 0 ? " " : "", frame.data[i]);
		}
		cout << endl;

		nbytes = write(s, &frame, sizeof(struct can_frame));
	}
	close(s);
}
