// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * HID driver for Chu Yuen Keyboard
 * Copyright (c) 2019 Hemanth Bollamreddi
*/

#include <linux/hid.h>
#include <linux/module.h>

MODULE_AUTHOR("Hemanth Bollamreddi <blmhemu@gmail.com>");
MODULE_DESCRIPTION("HID Keyboard driver for Chu Yuen (Holtek) Keyboard.");
MODULE_LICENSE("GPL v2");

//TODO: If put in mainstream kernel, modify this file to include the VID and PID.
//#include "hid-ids.h"
#define USB_VENDOR_ID_CHUYUEN 0x1044
#define USB_DEVICE_ID_CHUTUEN_HIDKBD 0x7A39

#define HIDRAW_FN_ESC 0x04000084
#define HIDRAW_FN_F2 0x0400007C
#define HIDRAW_FN_F4 0x0400007E
#define HIDRAW_FN_F3 0x0400007D
#define HIDRAW_FN_F6 0x04000080
#define HIDRAW_FN_F10 0x04000081
#define HIDRAW_FN_F11 0x04000082
#define HIDRAW_FN_F12 0x04000083

#define make_u32(a, b, c, d) a << 24 | b << 16 | c << 8 | d

static int chuyuen_kbd_raw_event(struct hid_device *hdev, struct hid_report *report, u8 *rd, int size)
{
	if (report->id == 4 && size == 4)
	{
		u32 hidraw = make_u32(rd[0], rd[1], rd[2], rd[3]);
		// printk("Chu Yuen Raw Event. hidraw code : %x", hidraw);
		switch (hidraw)
		{
		case HIDRAW_FN_F3:
			rd[0] = 0x03;rd[1] = 0x70;rd[2] = 0x00;
			hid_report_raw_event(hdev, HID_INPUT_REPORT, rd, 4, 0);
			rd[0] = 0x03;rd[1] = 0x00;rd[2] = 0x00;
			return 1;
		case HIDRAW_FN_F4:
			rd[0] = 0x03;rd[1] = 0x6f;rd[2] = 0x00;
			hid_report_raw_event(hdev, HID_INPUT_REPORT, rd, 4, 0);
			rd[0] = 0x03;rd[1] = 0x00;rd[2] = 0x00;
			return 1;
		default:
			return 0;
			break;
		}
	}
	return 0;
}

static int chuyuen_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	// printk("Chu Yuen Driver Loaded.");
	int ret;
	hdev->quirks |= HID_QUIRK_INPUT_PER_APP;

	ret = hid_parse(hdev);
	if (ret)
		return ret;

	return hid_hw_start(hdev, HID_CONNECT_DEFAULT);
}

static const struct hid_device_id chuyuen_kbd_devices[] = {
	{HID_USB_DEVICE(USB_VENDOR_ID_CHUYUEN, USB_DEVICE_ID_CHUTUEN_HIDKBD)},
	{}
};
MODULE_DEVICE_TABLE(hid, chuyuen_kbd_devices);

static struct hid_driver chuyuen_kbd_driver = {
	.name = "Chu Yuen",
	.id_table = chuyuen_kbd_devices,
	.probe = chuyuen_probe,
	.raw_event = chuyuen_kbd_raw_event};
module_hid_driver(chuyuen_kbd_driver);
