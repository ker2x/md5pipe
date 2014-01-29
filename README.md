md5pipe
=======

acting as a pipe (sending to stdout what it's receiving from stdin) and generating a md5 from the stream.
Yes, it's usefull.

eg : cat * | gzip | md5pipe | ftp ...
