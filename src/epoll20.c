#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>

/*
 *           t0
 *            | (ew)
 *           e0
 *            | (et)
 *           e1
 *            | (et)
 *           s0
 */

int main(int argc, char *argv[])
{
	int sfd[2];
	int efd[2];
	struct epoll_event e;

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sfd) < 0)
		goto out;

	efd[0] = epoll_create(1);
	if (efd[0] < 0)
		goto out;

	efd[1] = epoll_create(1);
	if (efd[1] < 0)
		goto out;

	e.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(efd[1], EPOLL_CTL_ADD, sfd[0], &e) < 0)
		goto out;

	e.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[1], &e) < 0)
		goto out;

	if (write(sfd[1], "w", 1) != 1)
		goto out;

	if (epoll_wait(efd[0], &e, 1, 0) != 1)
		goto out;

	if (epoll_wait(efd[0], &e, 1, 0) != 0)
		goto out;

	close(efd[0]);
	close(efd[1]);
	close(sfd[0]);
	close(sfd[1]);

	return 0;

out:
	return -1;
}
