/*
 utsname-test.c
 GNU General Public License version 2.0
 thom o'connor 2020-05-29

 compile:
 gcc -o utsname-test utsname-test.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <sys/mman.h>

#ifndef _LINUX_UTSNAME_H
#include <sys/utsname.h>
#endif

#if defined __has_include
#  if __has_include("/etc/redhat-release")
      #define VERSION_RHEL "rhel"
#  endif
#endif

int main(void) {
   const char ident_rhel8[] = "el8";
   const char ident_rhel7[] = "el7";

   struct utsname host;
   struct os
   {
      char* return_str;
      char version[64];
   } my_os;

   if (uname(&host) != 0) {
      perror("uname");
      exit(EXIT_FAILURE);
   }

   printf("host.sysname = %s\n", host.sysname);
   printf("host.nodename = %s\n", host.nodename);
   printf("host.release = %s\n", host.release);
   printf("host.version = %s\n", host.version);
   printf("host.machine = %s\n", host.machine);

   #ifdef _GNU_SOURCE
      printf("host.domainname = %s\n", host.domainname);
   #endif

   if((my_os.return_str = strstr(host.release, ident_rhel8))) {
      strcpy(my_os.version,"rhel8");
      printf("Redhat version is: %s\n", my_os.return_str);
      printf("Version is: %s\n", my_os.version);
   }
   else if ((my_os.return_str = strstr(host.release, ident_rhel7))) {
      strcpy(my_os.version,"rhel7");
      printf("Redhat version is: %s\n", my_os.return_str);
      printf("Version is: %s\n", my_os.version);
   }
   else {
      printf("Version not identified");
   }

   return(EXIT_SUCCESS);
}
