Lab 2.5 - Depth-limiting Web Crawler
====================================

This laboratory is based on a web crawler with a small modification. The change is adding the depth flag to the execution command, so when adding `-depth=3`, then only URLs reachable by at most 3 links will be fetched.

In order to run the program do the next thing:
```
go run crawl3.go -depth=# link
```

Test Cases
==========
Some test cases:

```
# Test 1
go run crawl3.go -depth=2 https://google.com/

# Test 2
go run crawl3.go -depth=3 http://www.gopl.io/

# Test 3
go run crawl3.go -depth=1  http://www.gopl.io/

```
