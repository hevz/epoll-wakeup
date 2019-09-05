#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>

/*
 *          t0
 *           | (ew)
 *          e0
 *           | (lt)
 *          s0
 */

int main(int argc, char *argv[])
{
	int sfd[2];
	int efd;
	struct epoll_event e;

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sfd) < 0)
		goto out;

	efd = epoll_create(1);
	if (efd < 0)
		goto out;

	e.events = EPOLLIN;
	if (epoll_ctl(efd, EPOLL_CTL_ADD, sfd[0], &e) < 0)
		goto out;

	if (write(sfd[1], "w", 1) != 1)
		goto out;

	if (epoll_wait(efd, &e, 1, 0) != 1)
		goto out;

	if (epoll_wait(efd, &e, 1, 0) != 1)
		goto out;

	close(efd);
	close(sfd[0]);
	close(sfd[1]);

	return 0;

out:
	return -1;
}
