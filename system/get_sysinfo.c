#include <sys/sysinfo.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <grp.h>

int main() {
	struct sysinfo sys_info;
	struct group* grp;

	gid_t gid;
	char** users;

	int days, hours, mins, x = 1;

	system("clear");  
	printf("\033[4;40m            Systems information                   \033[0;m \n");
	if(sysinfo(&sys_info) != 0)
		perror("sysinfo");

	days = sys_info.uptime / 86400;
	hours = (sys_info.uptime / 3600) - (days * 24);
	mins = (sys_info.uptime / 60) - (days * 1440) - (hours * 60);

	printf("\033[1;33m  Uptime: \033[0;36m %ddays, %dhours, %dminutes, %ldseconds \033[0;m \n",
			days, hours, mins, sys_info.uptime % 60);

	printf("\033[1;33m  Load Avgs: \033[0;m 1min(%ld) 5min(%ld) 15min(%ld) \n",
			sys_info.loads[0], sys_info.loads[1], sys_info.loads[2]);

	printf("\033[1;33m  Total Ram: \033[0;m %ldk \t Free: %ldk \n", sys_info.totalram / 1024, sys_info.freeram / 1024);
	printf(" \033[1;33m Shared Ram: \033[0;m %ldk ", sys_info.sharedram / 1024);
	printf("  Buffered Ram: %ldk \n", sys_info.bufferram / 1024);
	printf("\033[1;33m  Total Swap: \033[0;m %ldk \t Free swap: %ldk \n", sys_info.totalswap / 1024, sys_info.freeswap / 1024);
	printf("\033[1;33m  Total High Memory: \033[0;m %ldk  Free high memory: %ldk \033[0;m \n", sys_info.totalhigh / 1024, sys_info.freehigh / 1024);
	printf(" \n");
	printf("\033[1;44m Total Number of processes: %d \033[0;m \n", sys_info.procs);  
	gid = getgid();
	printf("  Group ID: \033[031m %d", gid);
	if((grp = getgrgid(gid)) == NULL ) return 1;
	printf("\033[0;m Group %s ", grp->gr_name );
	printf("\n  Users in your group ");
	for( users = grp->gr_mem; *users != NULL; users++,++x ); printf( "%d", ++x);     
	if(strcmp(grp->gr_passwd,"x") == 0) printf("  Password is protected by shadow file. \n");
	else printf("Password: %s ", grp->gr_passwd);   

	return 0;
}
