#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>

/*
 *           t0
 *            | (ew)
 *           e0
 *     (et) /  \ (et)
 *        s0    s2
 */

int main(int argc, char *argv[])
{
	int sfd[4];
	int efd;
	struct epoll_event events[2];

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[0]) < 0)
		goto out;

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[2]) < 0)
		goto out;

	efd = epoll_create(1);
	if (efd < 0)
		goto out;

	events[0].events = EPOLLIN | EPOLLET;
	if (epoll_ctl(efd, EPOLL_CTL_ADD, sfd[0], events) < 0)
		goto out;

	events[0].events = EPOLLIN | EPOLLET;
	if (epoll_ctl(efd, EPOLL_CTL_ADD, sfd[2], events) < 0)
		goto out;

	if (write(sfd[1], "w", 1) != 1)
		goto out;

	if (write(sfd[3], "w", 1) != 1)
		goto out;

	if (epoll_wait(efd, events, 2, 0) != 2)
		goto out;

	if (epoll_wait(efd, events, 2, 0) != 0)
		goto out;

	close(efd);
	close(sfd[0]);
	close(sfd[1]);
	close(sfd[2]);
	close(sfd[3]);

	return 0;

out:
	return -1;
}
