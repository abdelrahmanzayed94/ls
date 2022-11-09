#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define l_FLAG_SHIFT	0
#define i_FLAG_SHIFT	1
#define a_FLAG_SHIFT	2
#define R_FLAG_SHIFT	3
#define l_FLAG_POS	(1 << l_FLAG_SHIFT)
#define i_FLAG_POS	(1 << i_FLAG_SHIFT)
#define a_FLAG_POS	(1 << a_FLAG_SHIFT)
#define R_FLAG_POS	(1 << R_FLAG_SHIFT)

typedef struct
{
	uint16_t others_x:1;
	uint16_t others_w:1;
	uint16_t others_r:1;
	uint16_t group_x:1;
	uint16_t group_w:1;
	uint16_t group_r:1;
	uint16_t owner_x:1;
	uint16_t owner_w:1;
	uint16_t owner_r:1;
	uint16_t sticky:1;
	uint16_t sgid:1;
	uint16_t suid:1;
	uint16_t file_type:4;
} mode_fields_s;

typedef union
{
	mode_fields_s fields;
	uint16_t value;
} mode_u;


void mode_parser(mode_u mode, char* buf)
{
	char others_x = (mode.fields.others_x == 1)? 'x' : '-';
	char others_w = (mode.fields.others_w == 1)? 'w' : '-';
	char others_r = (mode.fields.others_r == 1)? 'r' : '-'; 
	char group_x = (mode.fields.group_x == 1)? 'x' : '-';
	char group_w = (mode.fields.group_w == 1)? 'w' : '-';
	char group_r = (mode.fields.group_r == 1)? 'r' : '-'; 
	char owner_x = (mode.fields.owner_x == 1)? 'x' : '-';
	char owner_w = (mode.fields.owner_w == 1)? 'w' : '-';
	char owner_r = (mode.fields.owner_r == 1)? 'r' : '-';
	char file_type = '-'; //regular file
	
	if(S_ISDIR(mode.value))
		file_type = 'd';
	else if(S_ISCHR(mode.value))
		file_type = 'c';
	else if(S_ISBLK(mode.value))
		file_type = 'b';
	else if(S_ISFIFO(mode.value))
		file_type = 'p';
	else if(S_ISLNK(mode.value))
		file_type = 'l';
	else if(S_ISSOCK(mode.value))
		file_type = 's';

	//exception for sticky bit
	if(mode.fields.sticky == 1 && mode.fields.others_x == 1)
		others_x = 't';
	
	sprintf(buf,"%c%c%c%c%c%c%c%c%c%c", 
		file_type,
		owner_r,
		owner_w,
		owner_x,
		group_r,
		group_w,
		group_x,
		others_r,
		others_w,
		others_x);
}

void time_parser(time_t* tv, char* buf)
{
	char result[26];
	ctime_r(tv, result);
	
	strncpy(buf, &result[4], 12);
}

int ls_function(char* path, uint8_t flags)
{
	int ret_val = 0;
	DIR* dirp = opendir(path);
	char* filename = malloc(256);
	struct stat statbuf;
	struct passwd* passwdp;
	struct group* group_p; 
	mode_u mode;
	char mode_buf[11];
	char time_buf[13];
	
	if(dirp == NULL)
	{
		if(errno == EACCES)
		{
			fprintf(stderr, "permission denied!!\n");
		}
		else if(errno == ENOTDIR)
		{
			fprintf(stderr, "\"%s\" is not a directory!!\n", path);
		}
		else if(errno == ENOENT)
		{
			fprintf(stderr, "myls: cannot access '%s': No such file or directory\n", path);
		}
		else
		{
			fprintf(stderr, "error number %d in opening \"%s\"\n", errno, path);
		}
		
		ret_val = -1;
		goto function_exit;
	}
	
	struct dirent * direntp;
	
	while((direntp = readdir(dirp)) != NULL)
	{
		filename = realloc(filename, strlen(path) + strlen(direntp->d_name) + 2);
		strcat(filename, path);
		strcat(filename, "/");
		strcat(filename, direntp->d_name);
		//printf("filename = %s\n", filename);
		
		ret_val = stat(filename, &statbuf);	
		
		passwdp = getpwuid(statbuf.st_uid);
		group_p = getgrgid(statbuf.st_gid);
		mode.value = statbuf.st_mode;
		//printf("mode.value = %x\n", mode.value);
		mode_parser(mode, mode_buf);
		
		time_parser(&statbuf.st_mtim.tv_sec, time_buf);
		
		//check for 'a' flag
		if(((flags & a_FLAG_POS) == 0) && (direntp->d_name[0] == '.'))
		{	
			filename[0] = '\0';
			continue;
		}
		
		//check for 'i' flag
		if(flags & i_FLAG_POS)
		{
			printf("%-10lu ", direntp->d_ino);
		}
		
		//check for 'l' flag
		if(flags & l_FLAG_POS)
		{
			printf("%-12s %-5lu %-10s %-10s %-12lu %-15s", 
				mode_buf,
				statbuf.st_nlink,
				passwdp->pw_name,
				group_p->gr_name,
				statbuf.st_size,
				time_buf);
		}
		
		printf("%-10s ", direntp->d_name);
		
		//add new line for 'l' flag
		if(flags & l_FLAG_POS)
		{
			printf("\n");
		}
		
		/* ls -lia:
		printf("%-10lu %-12s %-5lu %-10s %-10s %-12lu %-15s %-10s\n", 
			direntp->d_ino, 
			mode_buf,
			statbuf.st_nlink,
			passwdp->pw_name,
			group_p->gr_name,
			statbuf.st_size,
			time_buf,
			direntp->d_name);*/
		
		//reset filename value		
		filename[0] = '\0';
	}
	
	//already added for 'l' flag
	if((flags & l_FLAG_POS) == 0)
	{
		printf("\n");
	}
	
	free(filename);
	
function_exit:
	return ret_val;
}

int main(int argc, char** argv)
{
	int err = 0;
	int opt;
	uint8_t flags = 0;

	while ((opt = getopt(argc, argv, "liRa")) != -1) 
	{
		switch (opt) 
		{
			case 'l':
				flags |= l_FLAG_POS;
				break;
			case 'i':
				flags |= i_FLAG_POS;
				break;
			case 'a':
				flags |= a_FLAG_POS;
				break;
			case 'R':
				flags |= R_FLAG_POS;
				break;
			default:
				fprintf(stderr, "Usage: %s [-l] [-i] [-R] [-a] optional arguments\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	//printf("flags = 0x%x; optind = %d\n", flags, optind);
	//printf("name argument = %s\n", argv[optind]);
	
	if(argc == optind)
	{
		char* cwd = getcwd(NULL, 0);
		//printf("%s\n", cwd);
		err = ls_function(cwd, flags);
		free(cwd);
	}
	else
	{
		for(int i = optind; i < argc; i++)
		{	
			if(argc > 1 + optind)
				printf("%s:\n", argv[i]);
				
			err = ls_function(argv[i], flags);
			
			if(argc > 1 + optind && i != argc - 1)
				printf("\n");
		}
	}
	
	return 0;
}

