// SPDX-License-Identifier: BSD-3-Clause
/*
 * inih -- simple .INI file parser
 *
 * Copyright (c) 2009, Brush Technology
 * Copyright (c) 2012:
 *              Joe Hershberger, National Instruments, joe.hershberger@ni.com
 * All rights reserved.
 *
 * Go to the project home page for more info:
 * http://code.google.com/p/inih/
 */

#include <common.h>
#include <command.h>
#include <env.h>
#include <ini.h>
#include <linux/ctype.h>
#include <linux/string.h>

static int ini_cmd_handler(void *user, char *section, char *name, char *value)
{
	char *requested_section = (char *)user;
#ifdef CONFIG_CMD_INI_CASE_INSENSITIVE
	int i;

	for (i = 0; i < strlen(requested_section); i++)
		requested_section[i] = tolower(requested_section[i]);
	for (i = 0; i < strlen(section); i++)
		section[i] = tolower(section[i]);
#endif

	if (!strcmp(section, requested_section)) {
#ifdef CONFIG_CMD_INI_CASE_INSENSITIVE
		for (i = 0; i < strlen(name); i++)
			name[i] = tolower(name[i]);
		for (i = 0; i < strlen(value); i++)
			value[i] = tolower(value[i]);
#endif
		env_set(name, value);
		printf("ini: Imported %s as %s\n", name, value);
	}

	/* success */
	return 1;
}

static int do_ini(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	const char *section;
	char *file_address;
	size_t file_size;

	if (argc == 1)
		return CMD_RET_USAGE;

	section = argv[1];
	file_address = (char *)hextoul(argc < 3 ? env_get("loadaddr") : argv[2],
					NULL);
	file_size = (size_t)hextoul(argc < 4 ? env_get("filesize") : argv[3],
				     NULL);

	return ini_parse(file_address, file_size, ini_cmd_handler, (void *)section);
}

U_BOOT_CMD(
	ini, 4, 0, do_ini,
	"parse an ini file in memory and merge the specified section into the env",
	"section [[file-address] file-size]"
);
