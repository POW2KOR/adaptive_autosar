# DriveUpdate Link test stub for Software Update Client Minerva Adapter
This document describes the high-level design for the integration and testing of the NVidia DriveUpdate in our ecosystem.

# Abbreviations, acronyms and terminology
- NVDU: NVidia DriveUpdate, a mechanism used to update software under NVidia DriveOS.
- SWUC: Software Update client, Minerva component responsible for the software update.
- SWUCA: Software Update client adapter, a component used to align interfaces of Software Update client and NVidia
DriveUpdate.
- DUS: NVidia DriveUpdate server, a proprietary component used in NVidia DriveOS for performing software update.
- DULL: NVidia DriveUpdate Link library, a shared library used to communicate with the DUS.
- TUC: Test Update client, a component used as a test stub for the Software Update client.
- TDS: Test DriveUpdate server, a component used as a test stub for the NVidia DriveUpdate server.
- TDLL: Test DriveUpdate Link library, a component used instead of the original NVidia DriveUpdate Link library for
testing purposes


# General concept

## Design notes
In order to communicate with NVidia DriveUpdate, we need to pass requests from the Software Update client to the
NVidia DriveUpdate server. To achieve this, an intermediate entity called Software Update client adapter is used.

Software Update client communicates with Software Update client adapter via ara::com. Then, data from the requests is
used to call functions from the NVidia DriveUpdate Link library, which communicates with the NVidia DriveUpdate server
via a separate communication interface.


## Conceptual sequence diagram of using the NVidia DriveUpdate mechanism
The following diagram illustrates this concept.

```plantuml

actor SWUC
participant SWUCA
participant DULL
participant DUS

activate SWUC
activate DUS

SWUC -> SWUCA ++ : update request\nover ara::com
SWUCA -> DULL ++ : call to\nshared library function
DULL -> DUS ++ : update request over\nDriveUpdate Link interface
DUS -> DUS : process\nrequest
return response over\nDriveUpdate Link interface
return response from\nlibrary function
return response\nover ara::com

```


# Test architecture

## Description
For testing the Software Update client adapter, we need to check the data flow from the both ends of this chain.
However, as long as NVidia DriveUpdate server and NVidia DriveUpdate Link are shipped by NVidia, we could probably not
focus on communications between them. Instead of that, we can control what data goes in and out of the NVidia
DriveUpdate Link library interfaces.

To control the test data flow, two test entities are required. The first one is the Test Update client. This entity is
responsible for emulating the Software Update client by generating test requests and analyzing responses on those
requests. The second one is the Test DriveUpdate server, which should process incoming test requests and reply on
them.

Then, in order to use the Test DriveUpdate server, we need a replacement for the original NVidia DriveUpdate Link
library. This replacement is the Test DriveUpdate Link library, which should provide the same interfaces as the
original one. All the corresponding calls to the DULL functions should be serialized and passed to the Test DriveUpdate
server, which emulates request processing and generates responses according to the test plan.

When a request is sent by the Test Update client, it is finally received by the Test DriveUpdate server. Here we can
check data integrity and generate a certain response for a given request. From the point of view of a test case logic,
we send a message, wait until it is received on the other side, check the received data, decide what to reply on
that, send a reply, then check the reply received by the Test Update client. This approach allows us to not hard-code
the expected behavior, but to alter it according to our needs, i.e. generate various errors for correct requests and
check for correct behavior of our Software Update client adapter for all possible inputs from both sides.


## Component diagram
The following diagram demonstrates how the described approach might be used for testing.

```plantuml

component "Test module" as TestModule {
agent "Test case logic" as logic
agent TUC
agent TDS
}

component "Adapter under test" as adapter {
agent SWUCA
agent TDLL
}

logic => TUC : request\ncontent
logic => TDS : response\ncontent
TUC --> SWUCA : request\nover ara::com
SWUCA => TDLL : shared library call
TDLL --> TDS : serialized\nrequest

```

The test case logic has control over both Test Update client and Test DriveUpdate server. They are coupled in a
single entity.

Software Update client adapter is dynamically linked with the Test DriveUpdate Link library.

## Test action sequence and data flow
The action sequence is:
- The Test case logic prepares a test request and expected data that should be passed to the NVidia DriveUpdate
interface.
- The Test case logic informs Test DriveUpdate server on what data it should expect and what it should respond on it.
- The Test case logic invokes the Test Update client with the prepared request.
- The Test Update client sends the given request to our Software Update client adapter via ara::com.
- The Software Update client adapter receives the prepared request, processes it and calls the corresponding NVidia
DriveUpdate Link interfaces from the Test DriveUpdate Link library.
- The Test DriveUpdate Link library serializes information passed to it and sends it to the Test DriveUpdate server.
- The Test DriveUpdate server analyzes the request data, checks it against the expected data provided from the Test
case logic, reports status of this check to the Test case logic and sends prepared reply to the Test DriveUpdate Link
library.
- The Test DriveUpdate Link library receives reply from the Test DriveUpdate server and returns result to the calling
function.
-The Software Update client adapter analyzes the return data from call to the NVidia DriveUpdate Link interface and
sends corresponding response over ara::com to the Test Update client.
- The Test Update client analyzes the response and reports status to the Test case logic.
- The Test case logic decides if this test has passed or not basing on contents of the request, data received by the
Test DriveUpdate server, response sent to the Software Update client adapter by the Test DriveUpdate server, and the
response of the Software Update client adapter to the Test Update client.
