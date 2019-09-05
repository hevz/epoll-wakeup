#include <poll.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>

/*
 *           t0
 *            | (p)
 *           e0
 *     (lt) /  \ (lt)
 *        e1    e2
 *    (lt) |     | (lt)
 *        s0    s2
 */

int main(int argc, char *argv[])
{
	int sfd[4];
	int efd[3];
	struct epoll_event events[2];
	struct pollfd pfd;

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[0]) < 0)
		goto out;

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[2]) < 0)
		goto out;

	efd[0] = epoll_create(1);
	if (efd[0] < 0)
		goto out;

	efd[1] = epoll_create(1);
	if (efd[1] < 0)
		goto out;

	efd[2] = epoll_create(1);
	if (efd[2] < 0)
		goto out;

	events[0].events = EPOLLIN;
	if (epoll_ctl(efd[1], EPOLL_CTL_ADD, sfd[0], events) < 0)
		goto out;

	events[0].events = EPOLLIN;
	if (epoll_ctl(efd[2], EPOLL_CTL_ADD, sfd[2], events) < 0)
		goto out;

	events[0].events = EPOLLIN;
	if (epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[1], events) < 0)
		goto out;

	events[0].events = EPOLLIN;
	if (epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[2], events) < 0)
		goto out;

	if (write(sfd[1], "w", 1) != 1)
		goto out;

	if (write(sfd[3], "w", 1) != 1)
		goto out;

	pfd.fd = efd[0];
	pfd.events = POLLIN;
	if (poll(&pfd, 1, 0) != 1) {
		goto out;
	}

	if (epoll_wait(efd[0], events, 2, 0) != 2)
		goto out;

	pfd.fd = efd[0];
	pfd.events = POLLIN;
	if (poll(&pfd, 1, 0) != 1) {
		goto out;
	}

	if (epoll_wait(efd[0], events, 2, 0) != 2)
		goto out;

	close(efd[0]);
	close(efd[1]);
	close(efd[2]);
	close(sfd[0]);
	close(sfd[1]);
	close(sfd[2]);
	close(sfd[3]);

	return 0;

out:
	return -1;
}
