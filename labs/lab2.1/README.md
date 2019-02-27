Lab 2.1 - ClockWall
===================

This programs work as client (clockWall.go) and server (clock2.go). The server can be used many times just by changing the time zone and the port of use for each one, as shown below:
```
# Clock Servers initialization
$ TZ=US/Eastern    ./clock2 -port 8010 &
$ TZ=Asia/Tokyo    ./clock2 -port 8020 &
$ TZ=Europe/London ./clock2 -port 8030 &
```
To compile the clock2.go just do the nest thing:
```
go build clock2.go
```
After that, just run the server as shown above.
Once the servers are initialized, we need to do the same with the client. So in order to compile the program we need to do the following:
```
go build clockWall.go
```
Then to access the different time zones just run locally the executable with arguments that have fake time zones, like these ones (Note that the names of the cities that you give will be displayed, but the time zones will be the ones of TZ variable':
```
./clockWall NewYork=localhost:8010 Tokyo=localhost:8020 London=localhost:8030
```
