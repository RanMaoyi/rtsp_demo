# rtsp_demo
a demo of rtsp client with libcurl and a client to receive rtp packet

## How to use
- Start the rstp server, here using EasyDarwin, and EasyDarwin starts listening on port rstp10054.
- Push streams to rstp port 10054 using ffmpeg.
```
$ ffmpeg -re -stream_loop -1 -i ~/vedio/MVI_3144.MP4 -c copy -f rtsp rtsp://127.0.0.1:10054/stream
```
- Compile rtsp_client.c/rtp_client.c
```
$ gcc rtsp_client.c -lcurl -o rtsp_client
$ gcc rtp_client.c -o rtp_client
```
- Run rtsp_client to trigger the rstp server to push streams to port 36464
```
$. / rtsp_client RTSP://127.0.0.1:10054/stream
```
- Run rtp_client, which receives the rtp packet and resolves the timestamp field
```
$ ./rtp_client
recvfrom 127.0.0.1:30070 bytes: 1364
timestamp:b2 77 ff 8b
recvfrom 127.0.0.1:30070 bytes: 1260
timestamp:b2 78 07 8b
recvfrom 127.0.0.1:30070 bytes: 1298
```
