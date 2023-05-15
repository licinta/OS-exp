all:msg-pipe demo-pipe msg-buffline-server msg-buffline-client msg-shm
exec=msg-pipe demo-pipe msg-buffline-server msg-buffline-client msg-shm


clean:
	rm -rf $(exec)


msg-pipe:msg-pipe.c
	gcc msg-pipe.c -o msg-pipe

demo-pipe:demo-pipe.c
	gcc demo-pipe.c -o demo-pipe

msg-buffline-server:
	gcc msg-buffline-server.c -o msg-buffline-server

msg-buffline-client:
	gcc msg-buffline-client.c -o msg-buffline-client

msg-shm:
	gcc msg-shm.c -o msg-shm


