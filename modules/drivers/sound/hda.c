/*
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2015 Dale Weiler
 *
 */

#include <drivers/pci/pci.h>
#include <libc/printf.h>
#include <mod/module.h>
#include <mod/shell/shell.h>

struct hda_device {
	uint32_t pci_device;
};

static struct hda_device _device;

static void find_hda(uint32_t device, uint16_t vendorid, uint16_t deviceid, void * extra) {

	struct hda_device * hda = extra;

	if ((vendorid == 0x8086) && (deviceid == 0x2668)) {
		hda->pci_device = device;
	}

}

DEFINE_SHELL_FUNCTION(hda_test, "[debug] Intel HDA experiments") {

	if (!_device.pci_device) {
		fprintf(tty, "No HDA device found.\n");
		return 1;
	}
	fprintf(tty, "HDA audio device is at 0x%x.\n", _device.pci_device);

	return 0;
}

static int init(void) {
	BIND_SHELL_FUNCTION(hda_test);
	pci_scan(&find_hda, -1, &_device);
	if (!_device.pci_device) {
		return 1;
	}
	return 0;
}

static int fini(void) {
	return 0;
}

MODULE_DEF(hda, init, fini);
MODULE_DEPENDS(debugshell);


