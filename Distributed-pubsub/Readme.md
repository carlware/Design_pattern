
Requirements:
============


1) Is the data supposed to be received in sequence?

The telemetry data is sequenced and all streamed data is timestamped to prevent out of sequencing.

Dashboard data is updated based on those criteria.

 

2) Do the data items have relationship among them?

Yes within the data stream their’s a predefined structure and the persistent data is based on a relational enterprise data model

 

3) Are the publishers and subscribers, distributed? Multi node(machine).

Yes and within containers but all are exposed as services

 

4) Is the data structured with pre-defined attributes? Or Is the data with heterogenous attributes?

Both



Solution:
=========

1) Distributed transaction log needs atleast two tables:
     > table storing messages(blob)
     > connection table of publishers & subscribers - number of connections

2) Notify daemon invocation is deployment logic 
   Application layer within accept() socket should be http based application using DB api

3) DB api is the crucial component amongst these components. DB api uses mmap() share some data structures, across executables(publishers & subscribers)
   more about mmap() - https://godoc.org/github.com/edsrzf/mmap-go


4) DB api will be shared library, but not(statically linked)


Comments:
========

If there is an existing C implementation running in production, then my guess is, it's design should be similar to above. We just need to port C implementation to GoLang, because programming paradigm is similar for C & GoLang


