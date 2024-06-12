**TASK. Message dispatcher**

During this task you should create a class MessageDispatcher. This class should provide an API to publish 3 types of messages:
- GreenMessage - contains string and counter.
- BlueMessage - contains 2 double values.
- OrangeMessage - contains 2 strings, integer and double.
From the other hand it should also allow to subscribe to different message type using lambda or std::function objects. As a result if GreenMessage was published then all the subscribers should be notified by calling registered functions.

Write a multithreaded program with 2 threads for message generation(messages should be generated randomly). The main thread should run MessageDispatcher logic including different subscribers for that messages.
