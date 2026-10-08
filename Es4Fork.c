pid_t p = fork();
//-1     //int status
if (!p) {printf ("") scanf ("")}
exit (status)

wait(&status);
if (WIFEXITED(status))
